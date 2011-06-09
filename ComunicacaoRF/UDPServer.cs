/*
C# Network Programming 
by Richard Blum

Publisher: Sybex 
ISBN: 0782141765
*/
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class UDPServer
{
    public int recv;
    public byte[] data = new byte[12];

    IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 9050);

    Socket newsock = new Socket(AddressFamily.InterNetwork,
                    SocketType.Dgram, ProtocolType.Udp);

    public UDPServer(int port)
    {
        ipep = new IPEndPoint(IPAddress.Any, port);

        newsock = new Socket(AddressFamily.InterNetwork,
                        SocketType.Dgram, ProtocolType.Udp);
        newsock.Bind(ipep);
    }

    public void Execute_Test()
    {
        Console.WriteLine("Waiting for a client...");
        IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
        EndPoint tmpRemote = (EndPoint)(sender);        
        while (true)
        {
            recv = newsock.ReceiveFrom(data, ref tmpRemote);
        }
    }

    public void Execute()
    {
    }
}

