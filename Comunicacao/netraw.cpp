#include <sys/types.h>
#ifndef _WIN32
#include <sys/socket.h>
#include <sys/poll.h>
#endif

#include <stdio.h>
#ifndef _WIN32
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include "util.h"

#include "netraw.h"

namespace Net{

//====================================================================//
//  Net::Address: Network address class
//  (C) James Bruce
//====================================================================//

bool Address::setHost(const char *hostname,int port)
{
  // printf("%s %d\n",hostname,port);
  addrinfo *res = NULL;
  getaddrinfo(hostname,NULL,NULL,&res);
  if(!res) return(false);

  mzero(addr);
  addr_len = res->ai_addrlen;
  memcpy(&addr,res->ai_addr,addr_len);

  // set port for internet sockets
  sockaddr_in *sockname = (sockaddr_in*)(&addr);
  if(sockname->sin_family == AF_INET){
    sockname->sin_port = htons(port);
  }else{
    // TODO: any way to set port in general?
  }

  freeaddrinfo(res);
  return(true);
}

void Address::setAny(int port)
{
  mzero(addr);
  sockaddr_in *s = (sockaddr_in*)(&addr);
  s->sin_addr.s_addr = htonl(INADDR_ANY);
  s->sin_port = htons(port);
  addr_len = sizeof(sockaddr_in);
}

in_addr_t Address::getInAddr() const
{
  const sockaddr_in *s = (sockaddr_in*)(&addr);
  return(s->sin_addr.s_addr);
}

void Address::print(FILE *out) const
{
  if(!addr_len){
    printf("null");
    return;
  }

  sockaddr_in *sockname = (sockaddr_in*)(&addr);
  if(sockname->sin_family == AF_INET){
    unsigned a = ntohl(sockname->sin_addr.s_addr);
    unsigned short p = ntohs(sockname->sin_port);

    fprintf(out,"%d.%d.%d.%d:%d",
            (a>>24)&0xFF, (a>>16)&0xFF, (a>>8)&0xFF, a&0xFF, p);
  }else{
    fprintf(out,"?");
  }
}

//====================================================================//
//  Net::UDP: Simple raw UDP messaging
//  (C) James Bruce
//====================================================================//

#ifdef _WIN32
UDP::UDP()
{
  // Initialize Winsock
  int iResult;
  WSADATA wsaData;
  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0)
    printf("WSAStartup failed: %d\n", iResult);

  fd = -1;
  close();
}

UDP::~UDP()
{
  close();
  WSACleanup();
}
#endif

bool UDP::open(int port, bool share_port_for_multicasting, bool multicast_include_localhost, bool blocking)
{
  // open the socket
#ifdef _WIN32
  if(fd >= 0) closesocket(fd);
#else
  if(fd >= 0) ::close(fd);
#endif
  fd = socket(PF_INET, SOCK_DGRAM, 0);

  // set socket as non-blocking
#ifdef _WIN32
  u_long iMode = blocking ? 0 : 1;
  ioctlsocket(fd, FIONBIO, &iMode);
#else
  int flags = fcntl(fd, F_GETFL, 0);
  if(flags < 0) flags = 0;
  fcntl(fd, F_SETFL, flags | (blocking ? 0 : O_NONBLOCK));
#endif

  if (share_port_for_multicasting) {
    int reuse=1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse,sizeof(reuse))!=0) {
      fprintf(stderr,"ERROR WHEN SETTING SO_REUSEADDR ON UDP SOCKET\n");
      fflush(stderr);
    }
    /*if(setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, 1)!=0) {
      fprintf(stderr,"ERROR WHEN SETTING SO_REUSEPORT ON UDP SOCKET\n");
      fflush(stderr);
    }*/
  }

  if (multicast_include_localhost) {
    int yes = 1;
    // allow packets to be received on this host
    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, (const char*)&yes, sizeof(yes))!=0) {
        fprintf(stderr,"ERROR WHEN SETTING IP_MULTICAST_LOOP ON UDP SOCKET\n");
        fflush(stderr);
    }
  }



  // bind socket to port if nonzero
  if(port != 0){
    sockaddr_in sockname;
    sockname.sin_family = AF_INET;
    sockname.sin_addr.s_addr = htonl(INADDR_ANY);
    sockname.sin_port = htons(port);
    bind(fd,(struct sockaddr*)(&sockname),sizeof(sockname));
  }



  /*
  // allow port reuse (for when a program is quickly restarted)
  // (not sure we really need this)
  int one = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
  */

  return(true);
}

bool UDP::addMulticast(const Address &multiaddr,const Address &interface_)
{
  static const bool debug = false;
  struct ip_mreq imreq;
  imreq.imr_multiaddr.s_addr = multiaddr.getInAddr();
  imreq.imr_interface.s_addr = interface_.getInAddr();

  if(debug){
    printf("0x%08X 0x%08X\n",
           (unsigned)interface_.getInAddr(),
           (unsigned)INADDR_ANY);
  }

  //join multicast group
#ifdef _WIN32
  int ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       (const char*)&imreq, sizeof(imreq));
#else
  int ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       &imreq, sizeof(imreq));
#endif
  if(debug) printf("ret=%d\n",ret);
  if(ret != 0)
    return false;

  //set multicast output interface
#ifdef _WIN32
  ret = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF,
    (const char*)&imreq.imr_interface.s_addr, sizeof(imreq.imr_interface.s_addr));
#else
  ret = setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF,
                   &imreq.imr_interface.s_addr, sizeof(imreq.imr_interface.s_addr));
#endif
  if(debug) printf("ret=%d\n",ret);

  return(ret == 0);
}

void UDP::close()
{
#ifdef _WIN32
  if(fd >= 0) closesocket(fd);
#else
  if(fd >= 0) ::close(fd);
#endif
  fd = -1;

  sent_packets = 0;
  sent_bytes   = 0;
  recv_packets = 0;
  recv_bytes   = 0;
}

bool UDP::send(const void *data,int length,const Address &dest)
{
#ifdef _WIN32
  int len = sendto(fd,(const char*)data,length,0,&dest.addr,dest.addr_len);
#else
  int len = sendto(fd,data,length,0,&dest.addr,dest.addr_len);
#endif

  if(len > 0){
    sent_packets++;
    sent_bytes += len;
  }

  return(len == length);
}

int UDP::recv(void *data,int length,Address &src)
{
  src.addr_len = sizeof(src.addr);
#ifdef _WIN32
  int len = recvfrom(fd,(char*)data,length,0,&src.addr,(int*)&src.addr_len);
#else
  int len = recvfrom(fd,data,length,0,&src.addr,&src.addr_len);
#endif

  if(len > 0){
    recv_packets++;
    recv_bytes += len;
  }

  return(len);
}

#ifndef _WIN32
bool UDP::wait(int timeout_ms) const
{
  pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLIN;
  pfd.revents = 0;

  return(poll(&pfd,1,timeout_ms) == 1);
}
#endif

}; // namespace Net

//====================================================================//
//  Testing Code
//====================================================================//
// compile with: g++ -g -Wall -O2 -DNETRAW_TEST netraw.cc -o nettest

#ifdef NETRAW_TEST

static const int Size = 32;

const char *hostname = "localhost";
int port = 2000;

void EchoServer()
{
  Net::UDP net;
  Net::Address addr;

  char msg[Size+1];
  net.open(port);

  while(true){
    if(net.wait()){
      int l = net.recv(msg,Size,addr);
      if(l > 0){
        msg[l] = 0;

        printf("["); addr.print();
        printf("]: %s",msg);
        if(msg[l-1] != '\n') printf("\n");

        net.send(msg,l,addr);
      }
    }
  }

  net.close();
}

void EchoClient()
{
  Net::UDP net;
  Net::Address addr,raddr;
  char msg[Size+1];
  int l;

  addr.setHost(hostname,port);
  net.open();

  while(fgets(msg,Size,stdin)){
    l = strlen(msg);
    net.send(msg,l,addr);

    net.wait(1000);
    l = net.recv(msg,Size,raddr);

    msg[l] = 0;
    printf("reply: %s",msg);
  }
}

int main(int argc, char **argv)
{
  char ch;
  bool server = false;
  bool client = false;

  while((ch = getopt(argc, argv, "sc:p:")) != EOF){
    switch(ch){
      case 's': server = true; break;
      case 'c': client = true; hostname = optarg; break;
      case 'p': port = atoi(optarg); break;
    }
  }

  if(server == client) exit(1);

  if(server){
    EchoServer();
  }else{
    EchoClient();
  }
}
#endif