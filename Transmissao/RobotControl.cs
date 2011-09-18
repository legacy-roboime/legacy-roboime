using System;
using System.Collections.Generic;
using System.Timers;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using LR;

namespace ControleRobo
{
    class RobotControl
    {
        #region Variables
        private int numRobots;

        private int serverPort = 9050;
        private int clientPort = 9876;

        private UDPServer server;

        private TransmissorRFM12USB transmitter;
        private UdpClient simulationClient;

        private string intelData;
        private byte[] intelTranslatedData;
        private byte[] intelTranslatedDataToBiWheel;
      
        private byte[] robotData;
        private string robotTranslatedBuffer;

        private int priorityRobot;

        private static System.Timers.Timer sendTimer;

        #endregion

        public void UDPSend(object sender, ElapsedEventArgs e)
        {
            this.server.sendData = Encoding.ASCII.GetBytes(" ");
            if (server.receivedData != null)
            {
                this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                Console.WriteLine(intelData);
                this.intelTranslatedData = Protocols.TranslateProtocol(intelData, false);
                Console.WriteLine(Encoding.ASCII.GetString(intelTranslatedData));
            }
            if (intelTranslatedData != null)
            {
                simulationClient.Send(intelTranslatedData, intelTranslatedData.Length);
            }
            //String temp = "5 0\n";
            //simulationClient.Send(Encoding.ASCII.GetBytes(temp), Encoding.ASCII.GetByteCount(temp));
        }
        public void TxSendReceive(object sender, ElapsedEventArgs e)
        {
            if (server.receivedData != null)
            {
                this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                Console.WriteLine(intelData);
                this.intelTranslatedData = Protocols.TranslateProtocol(intelData, true);
                this.intelTranslatedDataToBiWheel = Protocols.TranslateProtocolToBiWheel(intelData, true);
            }
            if (intelTranslatedData != null)
            {
               /* for (int i = 0; i < 35; i++)
                    intelTranslatedData[i + 3] = 1;
                intelTranslatedData[3] = 1;
                intelTranslatedData[10] = 2;
                intelTranslatedData[17] = 3;
                intelTranslatedData[24] = 4;
                intelTranslatedData[31] = 5;*/
                
                transmitter.Transmitir(intelTranslatedData);
                foreach (byte b in intelTranslatedData)
                {
                    Console.Write(b);
                    Console.Write("\t");
                }
                Console.WriteLine();

                transmitter.Transmitir(intelTranslatedDataToBiWheel);
                foreach (byte b in intelTranslatedDataToBiWheel)
                {
                    Console.Write(b);
                    Console.Write("\t");
                }
                Console.WriteLine();
            }
            /*
            string robotBuffer="";
            int[] receivedRobots = new int[numRobots];
            bool stopTrying = false;
            DateTime time = DateTime.Now;

            while (!stopTrying)
            {
                robotData = Encoding.ASCII.GetBytes(transmitter.Receber());
                robotBuffer += Protocols.ReverseTranslateProtocol(robotData);

                if (DateTime.Now.Subtract(time).Milliseconds > 50)
                    stopTrying = true;  
            }
            this.server.sendData = Encoding.ASCII.GetBytes(robotBuffer);*/
        }
        public void StartCommunication(bool realTransmitter)
        {
          
            server = new UDPServer(serverPort);
            Thread UDPServerThread = new Thread(server.Execute);
            UDPServerThread.Start();
            while (!UDPServerThread.IsAlive) ;
            Thread.Sleep(1);

            if (realTransmitter)
            {
                transmitter = new LR.TransmissorRFM12USB();
                transmitter.Inicializar("VIVATxRx", "IME");
                sendTimer = new System.Timers.Timer(100);

                sendTimer.Elapsed += new ElapsedEventHandler(TxSendReceive);
                sendTimer.Enabled = true;

                string blah = "";
                while (blah != "quit")
                {
                    blah = Console.ReadLine();
                }

            }
            else
            {
                this.simulationClient = new UdpClient("127.0.0.1", clientPort);
                sendTimer = new System.Timers.Timer(70);
                sendTimer.Elapsed += new ElapsedEventHandler(UDPSend);
                sendTimer.Enabled = true;

                string blah = "";
                while (blah != "quit")
                {
                    blah = Console.ReadLine();
                }
            }
        }

        static void Main(string[] args)
        {
            
            Console.WriteLine("Módulo de Transmissão - Emissao");
            RobotControl comm = new RobotControl();
            /*
            ConsoleKey[] keys = {ConsoleKey.W, ConsoleKey.A, ConsoleKey.S, ConsoleKey.D, ConsoleKey.Q, ConsoleKey.E};
            KeyboardController controller = new KeyboardController(2, keys);
            controller.Start();
            
            Controller[] controllers = {controller};
            */
            comm.StartCommunication(true);
            

            /*
            Console.WriteLine("Módulo de Transmissão - Recepcao");
            RobotControl comm = new RobotControl();

            while (true)
            {
                TransmissorRFM12USB transmitter = new LR.TransmissorRFM12USB();
                transmitter.Inicializar("VIVATxRx", "IME");
                string data;
                byte[] bytes;
                System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();
                while (true)
                {
                    data = transmitter.Receber();
                    bytes = encoding.GetBytes(data);
                    foreach(byte i in bytes)
                        Console.Write(i.ToString());
                    Console.WriteLine();
                }
            }
            */
        }
    }
}
