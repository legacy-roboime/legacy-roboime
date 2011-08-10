using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ControleRobo
{
    class Protocols
    {
        private static float kickerVelocity = 6;
        private static float dribblerVelocity = 6;
        private static float wheelVelocity = 6;

        public static byte ScaleVelocity(float realVelocity, float minVelocity, float maxVelocity)
        {
            float scaledspeed;
            if (realVelocity > maxVelocity)
                throw (new System. Exception("Given velocity exceeds maximum velocity for the component."));
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
            if (robotData[2] == (byte)0)
            {
                splitData[0] = ((int)robotData[1]).ToString();
                splitData[1] = (-Math.Sign(ReverseScaleVelocity(robotData[3], 0, 100))).ToString(); //Returns -1 if no ball, 1 if has ball
                splitData[2] = (Math.Abs(ReverseScaleVelocity(robotData[3], 0, 100))).ToString(); //Battery level
                splitData[3] = ReverseScaleVelocity(robotData[3], 0, wheelVelocity).ToString();
                splitData[4] = ReverseScaleVelocity(robotData[4], 0, wheelVelocity).ToString();
                splitData[5] = ReverseScaleVelocity(robotData[5], 0, wheelVelocity).ToString();
                splitData[6] = ReverseScaleVelocity(robotData[6], 0, wheelVelocity).ToString();
            }
            if (robotData[2] == (byte)1)
            {
                splitData[0] = ((int)robotData[1]).ToString();
                splitData[1] = (-Math.Sign(ReverseScaleVelocity(robotData[3], 0, 100))).ToString(); //Returns -1 if no ball, 1 if has ball
                splitData[2] = (Math.Abs(ReverseScaleVelocity(robotData[3], 0, 100))).ToString(); //Battery level
            }
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
                translated = PreliminaryTranslation(intelData); 
                
                foreach (byte b in translated)
                    Console.Write(b.ToString() + " ");
                Console.WriteLine();
                Console.WriteLine(intelData);
                
            }
            #endregion
            //Protocolo para o simulador
            #region simulation
            else
            {
                string appendString = "15 0 0 ";
                intelData = string.Concat(appendString, intelData);
                translated = Encoding.ASCII.GetBytes(intelData);
            }
            #endregion
            return translated;
        }

        private static byte[] PreliminaryTranslation(string intelData)
        {
            byte[] translated;
            translated = new byte[36];
            int j = 0;
            translated[j] = 0x22;
            j++;
            byte k = 1;
            translated[j] = k;
            j++;
            k++;
            Console.WriteLine(k);
            string[] splitData = intelData.Split(new Char[] { ' ', '\n' });
            for (int i = 0; (i < splitData.Length) && j < 36; i++)
            {
                if (splitData[i] == "")
                    // Kicker
                    continue;
                else if ((j) % 7 == 6)
                {
                    // Dribbler
                    translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, kickerVelocity);
                    j++;
                }
                else if ((j) % 7 == (7) % 7)
                {
                    translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, dribblerVelocity);
                    j++;
                    if (k != 6)
                        translated[j] = k++;

                    j++;
                }
                else
                {
                    // Wheels
                    translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, wheelVelocity);
                    j++;
                }
                //Console.WriteLine(splitData[i] + " "+i.ToString());
                //Console.WriteLine(translated[j].ToString() + " " + j.ToString());                   
            }

            return translated;
        }
    }
}
