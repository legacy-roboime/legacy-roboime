using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ControleRobo
{
    class Protocols
    {
        private static float kickerVelocity = 2;
        private static float dribblerVelocity = 100;
        private static float wheelVelocity = 100;

        public static byte ScaleVelocity(float realVelocity, float minVelocity, float maxVelocity)
        {
            float scaledspeed;
            //if (realVelocity > maxVelocity)
                //throw (new System. Exception("Given velocity exceeds maximum velocity for the component."));

            if (realVelocity >= 0)
            {
                scaledspeed = (realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity);
            }
            else
            {
                realVelocity = Math.Abs(realVelocity);
                scaledspeed = 255 - ((realVelocity - minVelocity) * 127 / (maxVelocity - minVelocity));
            }
            int scaledint = (int) scaledspeed;
            //if (scaledint < -127) scaledint = -126;
            //if (scaledint > 255) scaledint = 255;
            //scaledint = scaledint < 0 ? 0 : scaledint;
            byte b = (byte)scaledint;
            //byte scaled = Byte.scaledint;
            return b;
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
            try
            {
                string[] splitData = new String[robotData.Length + 5];
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
            catch
            {
                return null;
            }
        }
        public static byte[] TranslateProtocol(string intelData, bool realTransmitter)
        {
            byte[] translated;
            // Protocolo para o robô
            #region realTransmitter
            if (realTransmitter)
            {
                translated = PreliminaryTranslation(intelData); 
                
              //  foreach (byte b in translated)
              //     Console.Write(b.ToString() + " ");
              //  Console.WriteLine();
              //  Console.WriteLine(intelData);
                
            }
            #endregion
            //Protocolo para o simulador
            #region simulation
            else
            {
                string appendString = "15 0 1 ";
                intelData = string.Concat(appendString, intelData);
                translated = Encoding.ASCII.GetBytes(intelData);
            }
            #endregion
            return translated;
        }

        private static byte[] PreliminaryTranslation(string intelData)
        {
            byte[] translated;
            
            translated = new byte[39];
            int j = 0;
            byte k = 1;
            
            translated[j] = 0xfe; j++;
            translated[j] = 0; j++;
            translated[j] = 44; j++;
            translated[j] = k; j++;
            k++;
            //Console.WriteLine(k);
            intelData = intelData.Replace('.', ',');
            string[] splitData = intelData.Split(new Char[] { ' ', '\n' });
            /*
            foreach (string s in splitData)
            {
                Console.WriteLine(s);
            }
             */
            for (int i = 0; (i < splitData.Length) && j < 38; i++)
            {
                if (splitData[i] == "")
                    
                    continue;
                // Kicker
                else if ((j-2) % 7 == 6)
                {
                    float f = float.Parse(splitData[i]);
                    translated[j] = ScaleVelocity(f, 0, dribblerVelocity);
                    //translated[j] = (byte)((int)float.Parse(splitData[i]));
                    j++;
                }
                else if ((j-2) % 7 == (7) % 7)
                {
                    // Dribbler
                    float f = float.Parse(splitData[i]);
                    translated[j] = (byte)(254 * f);
                    //translated[j] = ScaleVelocity(float.Parse(splitData[i]), 0, dribblerVelocity);
                    //translated[j] = (byte)((int)float.Parse(splitData[i]));
                    j++;
                    if (k != 6)
                    {
                        translated[j] = k++;

                    }
                    else
                    {
                        break;
                    }

                    j++;
                }
                else
                {
                    // Wheels
                    float f = float.Parse(splitData[i]);
                    translated[j] = ScaleVelocity(f, 0, wheelVelocity);
                    //translated[j] = (byte)( (int) float.Parse(splitData[i]));
                    j++;
                }
                //Console.WriteLine(splitData[i] + " "+i.ToString());
                //Console.WriteLine(translated[j].ToString() + " " + j.ToString());                   
            }
            translated[j] = 55;


            return translated;
        }
    }
}
