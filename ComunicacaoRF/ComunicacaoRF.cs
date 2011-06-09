using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using LR;

namespace ComunicacaoRF
{
    class ComunicacaoRF
    {
        private byte[] memoryData;
        private byte[] translatedData;
        private LR.TransmissorRFM12USB transmissorRFM12USB1;

        public bool Send(byte[] t, byte source, byte dest)
        {
            byte[] temp = new byte[2 + t.Length];
            temp[0] = source;
            temp[1] = dest;
            Array.Copy(t, 0, temp, 2, t.Length);
            return this.transmissorRFM12USB1.Transmitir(temp);
        }

        public void StorePacket(byte[] pacote, byte velocidade0, byte velocidade1, byte velocidade2, byte velocidade3, byte velocidade4, byte velocidade5, byte velocidade6, byte velocidade7, byte velocidade8, byte velocidade9)
        {
            pacote[0] = 0;
            pacote[1] = 0x22;//pacote com todos os paramentros dos robos
            pacote[2] = 0;
            pacote[3] = velocidade0;
            pacote[4] = velocidade1;
            pacote[5] = 1;
            pacote[6] = velocidade2;
            pacote[7] = velocidade3;
            pacote[8] = 2;
            pacote[9] = velocidade4;
            pacote[10] = velocidade5;
            pacote[11] = 3;
            pacote[12] = velocidade6;
            pacote[13] = velocidade7;
            pacote[14] = 4;
            pacote[15] = velocidade8;
            pacote[16] = velocidade9;
        }

        public byte[] TranslateProtocol(byte[] data)
        {
            return data;
        }

        public void StartCommunication()
        {
            UDPServer server = new UDPServer(9050);

            // Initializes the thread in which the UDP server will reside
            Thread UDPServerThread = new Thread(server.Execute_Test);
            UDPServerThread.Start();
            while (!UDPServerThread.IsAlive) ;
            Thread.Sleep(1);

            this.transmissorRFM12USB1 = new LR.TransmissorRFM12USB();
            this.transmissorRFM12USB1.Inicializar("VIVATxRx", "IME");
            

            while (true)
            {
                if (server.data != null)
                {                    
                        this.memoryData = server.data;
                        this.translatedData = TranslateProtocol(memoryData);
                        Send(this.translatedData, 0xfe, 0xff);
                        Console.WriteLine(Encoding.ASCII.GetString(server.data, 0, server.recv));
                }
            }
        }

        static void Main(string[] args)
        {
            ComunicacaoRF comm = new ComunicacaoRF();
            comm.StartCommunication();
        }
    }
}
