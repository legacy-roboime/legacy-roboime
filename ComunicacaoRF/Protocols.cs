using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ControleRobo
{
    class Protocols
    {
        private static float kickerVelocity = 100;
        private static float dribblerVelocity = 100;
        private static float wheelVelocity = 100;

        public static byte ScaleVelocity(float realVelocity, float minVelocity, float maxVelocity)
        {
            float scaledspeed;
            if (realVelocity > maxVelocity)
                throw (new Exception("Given velocity exceeds maximum velocity for the component."));
            if (realVelocity >= 0)
                scaledspeed = (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            else
                scaledspeed = 127 + (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            int scaledint = (int)scaledspeed;
            byte scaled = Byte.Parse(scaledint.ToString());
            return scaled;
        }
        public static float ReverseScaleVelocity(byte scaled, float minVelocity, float maxVelocity)
        {
            float realVelocity, scaledFloat;
            if (scaled > 127)
            {
                scaled -= 127;
                scaledFloat = -1*((float) scaled);
            }
            else
                scaledFloat = (float) scaled;
            realVelocity = minVelocity + scaledFloat * (maxVelocity - minVelocity) / 127;
            return realVelocity;
        }
        public static string ReverseTranslateProtocol(byte[] robotData)
        {
            string[] splitData = new String[robotData.Length-1];
            string temp = "";
            splitData[0] = ReverseScaleVelocity(robotData[1], 0, wheelVelocity).ToString();
            splitData[1] = ReverseScaleVelocity(robotData[2], 0, wheelVelocity).ToString();
            splitData[2] = ReverseScaleVelocity(robotData[3], 0, wheelVelocity).ToString();
            splitData[3] = ReverseScaleVelocity(robotData[4], 0, wheelVelocity).ToString();
            splitData[4] = ReverseScaleVelocity(robotData[5], 0, kickerVelocity).ToString();
            splitData[5] = ReverseScaleVelocity(robotData[6], 0, dribblerVelocity).ToString();
            foreach (string subString in splitData)
            {
                temp = String.Concat(temp, " ");
                temp = String.Concat(temp, subString);
            }
            temp = String.Concat(temp, '\n');
            return temp;
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
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, kickerVelocity);
                    else if ((i) % 6 == 5)
                    {
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, dribblerVelocity);
                        j++;
                        translated[j] = k++;
                    }
                    else
                        // Wheels
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, wheelVelocity);
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
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, kickerVelocity);
                    else if ((i) % 6 == 5)
                    {
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, dribblerVelocity);
                        j++;
                        translated[j] = k++;
                    }
                    else
                        // Wheels
                        translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, wheelVelocity);
                    j++;
                }
            }
            #endregion
            //Protocolo para o simulador
            #region simulation
            else
            {
                string[] splitData = intelData.Split(new Char[] { ' ', '\n' });
                for (int i = 0; i < numberControllers; i++)
                {
                    int startRobotInfo = 6 * (controllers[i].robotId - 1);
                    for (int j = 0; j < 6; j++)
                    {
                        if (controllers[i].issuedCommands[j] != Command.None)
                            splitData[startRobotInfo + j] = 30.ToString();
                        else
                            splitData[startRobotInfo + j] = 0.ToString();
                    }
                }
                foreach (string subString in splitData)
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
    }
}
