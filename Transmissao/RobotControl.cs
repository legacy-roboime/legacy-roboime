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
        private string intelData;
        private byte[] intelTranslatedData;
        private byte[] robotData;
        private string robotTranslatedData;

        private UDPServer server;

        private TransmissorRFM12USB transmitter;
        private UdpClient simulationClient;

        private static System.Timers.Timer sendTimer;
        private static System.Timers.Timer receiveTimer;

        private int serverPort = 9050;
        private int clientPort = 9876;
        #endregion

        public void UDPSend(object sender, ElapsedEventArgs e)
        {
            if (server.receivedData != null)
            {
                this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                this.intelTranslatedData = Protocols.TranslateProtocol(intelData, false);
                //Console.WriteLine(Encoding.ASCII.GetString(server.data, 0, server.recv));
            }
            if (intelTranslatedData != null)
                simulationClient.Send(intelTranslatedData, intelTranslatedData.Length);
        }
        public void TxSend(object sender, ElapsedEventArgs e)
        {
            if (server.receivedData != null)
            {
                this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                this.intelTranslatedData = Protocols.TranslateProtocol(intelData, true);
                //Console.WriteLine(Encoding.ASCII.GetString(server.data, 0, server.recv));
            }
            if (intelTranslatedData != null)
            {
                transmitter.Transmitir(intelTranslatedData);
            }
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
                sendTimer = new System.Timers.Timer(700);
                sendTimer.Elapsed += new ElapsedEventHandler(TxSend);
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
                sendTimer = new System.Timers.Timer(700);
                sendTimer.Elapsed += new ElapsedEventHandler(UDPSend);
                sendTimer.Enabled = true;

                string blah = "";
                while (blah != "quit")
                {
                    blah = Console.ReadLine();
                }
            }
        }
        public void StartCommunication(bool realTransmitter, Controller[] controllers)
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
                sendTimer = new System.Timers.Timer(700);
                sendTimer.Elapsed += new ElapsedEventHandler(TxSend);
                sendTimer.Enabled = true;

                while (true)
                {
                    if (server.receivedData != null)
                    {
                        this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                        this.intelTranslatedData = Protocols.TranslateProtocol(intelData, realTransmitter, controllers);
                        //Send(this.intelTranslatedData, 0xfe, 0xff);
                        //Console.WriteLine(Encoding.ASCII.GetString(server.data, 0, server.recv));
                    }
                }

            }
            else
            {
                this.simulationClient = new UdpClient("127.0.0.1", clientPort);
                sendTimer = new System.Timers.Timer(700);
                sendTimer.Elapsed += new ElapsedEventHandler(UDPSend);
                sendTimer.Enabled = true;

                if (server.receivedData != null)
                {
                    while (true)
                    {
                        this.intelData = Encoding.ASCII.GetString(server.receivedData, 0, server.recv);
                        this.intelTranslatedData = Protocols.TranslateProtocol(intelData, realTransmitter, controllers);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            
            //Console.WriteLine("Módulo de Transmissão - Emissao");
            //RobotControl comm = new RobotControl();
            
            //ConsoleKey[] keys = {ConsoleKey.W, ConsoleKey.A, ConsoleKey.S, ConsoleKey.D, ConsoleKey.Q, ConsoleKey.E};
            //KeyboardController controller = new KeyboardController(2, keys);
            //controller.Start();

            //Controller[] controllers = {controller};

            //comm.StartCommunication(true);
            

            
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
            
        }
    }
}
