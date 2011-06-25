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

        private static float kickerVelocity = 100;
        private static float dribblerVelocity = 100;
        private static float wheelVelocity = 100;

        private int serverPort = 9050;
        private int clientPort = 9876;
        #endregion

        public void UDPSend(object sender, ElapsedEventArgs e)
        {
            if (intelTranslatedData != null)
                simulationClient.Send(intelTranslatedData, intelTranslatedData.Length);
        }
        public void TxSend(object sender, ElapsedEventArgs e)
        {
            if (intelTranslatedData != null)
            {
                //    Send(this.intelTranslatedData, 0xfe, 0xff);
                byte[] temp = new byte[2 + intelTranslatedData.Length];
                temp[0] = 0xfe;
                temp[1] = 0xff;
                Array.Copy(intelTranslatedData, 0, temp, 2, intelTranslatedData.Length);
                transmitter.Transmitir(temp);
            }
        }
        public static byte ScaleVelocity(float realVelocity, float minVelocity, float maxVelocity)
        {
            float scaledspeed;
            if (realVelocity > maxVelocity)
                throw (new Exception("Given velocity exceeds maximum velocity for the component."));
            if (realVelocity >= 0)
                scaledspeed = (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            else
                scaledspeed = 255 - (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            int scaledint = (int)scaledspeed;
            byte scaled = Byte.Parse(scaledint.ToString());
            return scaled;
        }
        public static string ReverseTranslateProtocol(byte[] robotData)
        {
            return null;
        }
        public static byte[] TranslateProtocol(string intelData, bool realTransmitter)
        {
            byte[] translated;
            // Protocolo para o robô
            #region realTransmitter
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
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.kickerVelocity);
                    else if ((i) % 6 == 5)
                    {
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.dribblerVelocity);
                        j++;
                        translated[j] = k++;
                    }
                    else
                        // Wheels
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.wheelVelocity);
                    j++;
                }
            }
            #endregion
            //Protocolo para o simulador
            #region simulation
            else
            {
                string appendString = "13 0 4 ";
                System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding(); 

                intelData = string.Concat(appendString, intelData);
          

                translated = encoding.GetBytes(intelData);
            }
            #endregion
            return translated;
        }
        public static byte[] TranslateProtocol(string intelData, bool realTransmitter, Controller[] controllers)
        {
            int numberControllers = controllers.Length;
            string temp = "";
            byte[] translated;
            // TODO: Implementar controle pelo teclado para o robô real
            #region realTransmitter
            if (realTransmitter)
            {
                string[] splitData = intelData.Split(new Char[] { ' ', '\n' });
                for (int i = 0; i < numberControllers; i++)
                {
                    int startRobotInfo = 6 * (controllers[i].robotId - 1);
                    for (int l = 0; l < 6; l++)
                    {
                        if (controllers[i].issuedCommands[l] != Command.None)
                            splitData[startRobotInfo + l] = 30.ToString();
                        else
                            splitData[startRobotInfo + l] = 0.ToString();
                    }
                }

                translated = new byte[36];
                int j = 0;
                translated[j] = 0x22;
                j++;
                byte k = 1;
                translated[j] = k;
                j++;
                k++;

                for (int i = 0; i < splitData.Length; i++)
                {
                    if (splitData[i] == "")
                        // Kicker
                        continue;
                    else if ((i) % 6 == 4)
                        // Dribbler
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.kickerVelocity);
                    else if ((i) % 6 == 5)
                    {
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.dribblerVelocity);
                        j++;
                        translated[j] = k++;
                    }
                    else
                        // Wheels
                        translated[j] = RobotControl.ScaleVelocity(float.Parse(splitData[i]), 0, RobotControl.wheelVelocity);
                    j++;
                }
            }
            #endregion
            //Protocolo para o simulador
            #region simulation
            else
            {
                string[] splitData = intelData.Split(new Char[] {' ', '\n' });
                for (int i = 0; i < numberControllers; i++)
                {
                    int startRobotInfo = 6 * (controllers[i].robotId - 1);
                    for (int j = 0; j < 6; j++)
                    {
                        if(controllers[i].issuedCommands[j]!=Command.None)
                            splitData[startRobotInfo + j]=30.ToString();
                        else
                            splitData[startRobotInfo + j] = 0.ToString();
                    }
                }
                foreach(string subString in splitData)
                {
                    temp = String.Concat(temp, " ");
                    temp = String.Concat(temp, subString);
                }
                temp = String.Concat(temp, '\n');

                string appendString = "13 0 4";
                temp = string.Concat(appendString, temp);
                System.Text.ASCIIEncoding encoding = new System.Text.ASCIIEncoding();

                translated = encoding.GetBytes(temp);
            }
            #endregion
            return translated;
        }
        public void StartCommunication(bool realTransmitter)
        {
            server = new UDPServer(serverPort);
            //
            // TODO: Tirar isso daqui e colocar o protocolo do robô 
            //

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
                        this.intelTranslatedData = TranslateProtocol(intelData, realTransmitter);
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
                        this.intelTranslatedData = TranslateProtocol(intelData, realTransmitter);
                    }
                }
            }
        }
        public void StartCommunication(bool realTransmitter, Controller[] controllers)
        {
            server = new UDPServer(serverPort);
            //
            // TODO: Tirar isso daqui e colocar o protocolo do robô 
            //

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
                        this.intelTranslatedData = TranslateProtocol(intelData, realTransmitter, controllers);
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
                        this.intelTranslatedData = TranslateProtocol(intelData, realTransmitter, controllers);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Módulo de controle");
            RobotControl comm = new RobotControl();
            
            ConsoleKey[] keys = {ConsoleKey.W, ConsoleKey.A, ConsoleKey.S, ConsoleKey.D, ConsoleKey.Q, ConsoleKey.E};
            KeyboardController controller = new KeyboardController(2, keys);
            controller.StartReadingInput();

            Controller[] controllers = {controller};

            comm.StartCommunication(true);
        }
    }
}
