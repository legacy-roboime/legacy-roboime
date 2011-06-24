using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using LR;

namespace ComunicacaoRF
{
    class ComunicacaoRF
    {
        private string memoryData;
        private byte[] translatedData;

        private LR.TransmissorRFM12USB transmissorRFM12USB1;
        private UdpClient client;

        private static float kickerVelocity = 100;
        // em RPM
        private static float dribblerVelocity = 100;
        // em RPM
        private static float wheelVelocity = 100;
        // em RPM
        private int serverPort = 9050;
        private int clientPort = 30000;

        public bool Send(byte[] t, byte source, byte dest)
        {
            byte[] temp = new byte[2 + t.Length];
            temp[0] = source;
            temp[1] = dest;
            Array.Copy(t, 0, temp, 2, t.Length);
            return this.transmissorRFM12USB1.Transmitir(temp);
        }

        public void UDPClientSend()
        {
            while (true)
            {
                if (translatedData != null)
                    client.Send(translatedData, translatedData.Length);
            }
        }

        public static byte ScaleVelocity(float realVelocity, float minVelocity, float maxVelocity)
        {
            float scaledspeed;
            if (realVelocity >= 0)
                scaledspeed = (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            else
                scaledspeed = 255 - (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            int scaledint = (int)scaledspeed;
            byte scaled = Byte.Parse(scaledint.ToString());
            return scaled;
        }

        public static string ReverseTranslateProtocol(byte robotData)
        {
            return null;
        }

        public static byte[] TranslateProtocol(string intelData, bool realTransmitter)
        {
            byte[] translated;
            // Protocolo para o robô
            if (realTransmitter)
            {
                translated = new byte[36];
                int j = 0;
                translated[j] = 0x22;
                j++;
                byte k = 1;
                translated[j] = k;
                j++;
                k++;
                string[] splitData = intelData.Split(new Char[] { ' ', '\n' });

                for (int i = 0; i < splitData.Length; i++)
                {
                    if (splitData[i] == "")
                        // Kicker
                        continue;
                    else if ((i) % 6 == 4)
                        // Dribbler
                        translated[j] = ComunicacaoRF.ScaleVelocity(float.Parse(splitData[i]), 0, ComunicacaoRF.kickerVelocity);
                    else if ((i) % 6 == 5)
                    {
                        translated[j] = ComunicacaoRF.ScaleVelocity(float.Parse(splitData[i]), 0, ComunicacaoRF.dribblerVelocity);
                        j++;
                        translated[j] = k++;
                    }
                    else
                        // Wheels
                        translated[j] = ComunicacaoRF.ScaleVelocity(float.Parse(splitData[i]), 0, ComunicacaoRF.wheelVelocity);
                    j++;
                }
            }
            //Protocolo para o simulador
            else
            {
                string appendString = "13 0 4 ";
                intelData = string.Concat(appendString, intelData);

                System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();

                translated = encoding.GetBytes(intelData);

            }


            return translated;
        }

        public void StartCommunication(bool realTransmitter)
        {
            UDPServer server = new UDPServer(serverPort);

            // Initializes the thread in which the UDP server will reside
            Thread UDPServerThread = new Thread(server.Execute);
            UDPServerThread.Start();
            while (!UDPServerThread.IsAlive)
                ;
            Thread.Sleep(1);

            if (realTransmitter)
            {
                this.transmissorRFM12USB1 = new LR.TransmissorRFM12USB();
                this.transmissorRFM12USB1.Inicializar("VIVATxRx", "IME");

                while (true)
                {
                    if (server.data != null)
                    {
                        this.memoryData = Encoding.ASCII.GetString(server.data, 0, server.recv);
                        this.translatedData = TranslateProtocol(memoryData, realTransmitter);
                        Send(this.translatedData, 0xfe, 0xff);
                        //Console.WriteLine(Encoding.ASCII.GetString(server.data, 0, server.recv));
                    }
                }

            }
            else
            {
                this.client = new UdpClient("127.0.0.1", clientPort);
                Thread UDPClientThread = new Thread(UDPClientSend);
                UDPClientThread.Start();
                while (!UDPClientThread.IsAlive) ;
                Thread.Sleep(1);

                while (true)
                {

                    if (server.data != null) 
                    {
                        this.memoryData = Encoding.ASCII.GetString(server.data, 0, server.recv);
                        this.translatedData = TranslateProtocol(memoryData, realTransmitter);

                        //   for (int i = 0; i < translatedData.Length; i++)
                        //Console.WriteLine(translatedData[i]);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Comunicação RF");
            ComunicacaoRF comm = new ComunicacaoRF();
            //comm.translatedData = ComunicacaoRF.TranslateProtocol("-1.23 2.14 3.21 -4.1 5.321 -1.324 13.4 42.3 -12.2 43.1 12 32 43 12 54 23 76 43 23 30 45 54 5 7 52 -54 -23 34 54 55\n");
            //Console.WriteLine("");
            //for (int i = 0; i < comm.translatedData.Length; i++)
            //    Console.WriteLine(comm.translatedData[i]);

            comm.StartCommunication(false);
        }
    }
}
