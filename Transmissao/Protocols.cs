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
            int scaledint = (int)scaledspeed;
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
                scaledFloat = -1 * ((float)scaled);
            }
            else
                scaledFloat = (float)scaled;
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
        public static byte[] TranslateProtocolTeambots(string intelData, bool realTransmitter)
        {


            double[] SpeedLeft = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62.65724439, 71.31568189, 85.79657308, 104.7718167, 118.222461, 132.1113237, 143.0723787, 154.3770947, 165.4694082, 172.7353866, 183.3636709, 190.7088638, 198.7563957, 210.3038322, 214.5618697, 221.5605999, 228.3061997, 232.3872296, 237.9815248, 244.869752, 251.0918471, 256.6589595, 262.6882778, 264.5862994, 270.1499472, 275.2389783, 278.7940457, 283.665818, 287.7897552, 291.104673, 294.9637657, 299.7399416, 307.765746, 313.212701, 316.0360339, 319.8141218, 322.4996536, 325.32889, 326.1838548, 327.0931563, 328.8379304, 334.3917412, 334.8677387, 339.2578261, 346.8866027, 350.0958883, 354.5068086, 356.0412574, 360.478406, 363.12754, 363.1325063, 364.0330316, 364.9668997, 366.1428249, 368.0633707, 370.6255595, 373.2358249, 374.3376103, 378.3788826, 378.7029565, 379.8923823, 382.4897551, 382.7657282, 382.9289871, 388.5862394, 389.6460208, 390.6536888, 391.6562436, 392.7231926, 394.0503562, 395.3794573, 395.9354158, 396.4497001, 396.703431, 396.8729023, 399.4223257, 401.4084647, 402.7419257, 402.7895823, 407.0973776, 407.6783213, 408.2840241, 408.9625449, 409.2668431, 411.3740093, 411.5479874, 412.2036664, 412.2601458, 413.3281167, 414, 414.1231375, 414.2243549, 415, 415.5195459, 415.5804604, 416.2909535, 416.5379069, 417.3972099, 417.477917, 417.6420895, 417.8267316, 418.2855018, 419, 419.1785558, 419.2315144, 419.3164698, 419.7885725, 420, 420.3883692, 420.4001705, 421.1180257, 422.564144, -390.9295004, -389.305978, -389.1895293, -388.9490797, -388.8976619, -388.5226555, -388.4285601, -388.1496035, -387.7693004, -387.7643586, -386, -385.4982862, -384.9660693, -384.0798645, -382.8239141, -382.6175449, -381.8473145, -381.2527427, -379.3269271, -378.9629338, -378, -377.9989641, -377.4153979, -375.2473301, -374.5293061, -374.4836004, -374.3066714, -374.1048677, -373.5694728, -370.7325409, -366.9969497, -366.3863672, -365.9120346, -363.4795707, -360.8732563, -360.7872418, -358.9871306, -358.6883054, -358.2271637, -356.0553722, -354.7034747, -354.0658691, -353.8753418, -349.8147691, -348.4752175, -345.0056099, -344.8900031, -344.1017568, -343.2152318, -339.6845434, -338.1961386, -338.153692, -337.0096181, -335.4861261, -334.5087221, -332.6476162, -330.4736149, -329.5207165, -328.9806371, -325.1416836, -324.3187818, -323.3200132, -323.1775676, -320.3431231, -315.8369656, -315.196814, -310.8679642, -310.4699448, -305.5827386, -303.3257481, -301.7419253, -298.1520047, -293.9651534, -291.8443669, -289, -285.1608804, -280.7170635, -278.2597403, -275.6886533, -270.9785778, -268.5411399, -265.5323432, -262.3438548, -258.6127817, -254.8364298, -249.5775983, -247.5598937, -242.1904956, -237.2830932, -233.051482, -228.916103, -223.7779488, -218.8018362, -212.3464357, -206.4275627, -201.0986841, -195, -189.8921905, -182.0455897, -174.7625357, -167.9800594, -158.6241015, -150.8919175, -144.2062392, -134.1609877, -125.232515, -114.0218921, -102.2920722, -89.91882298, -79.66315531, -65.19644195, -51.14466356, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //16 até 239
            double[] SpeedRight = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 77.16992567, 92.79721917, 111.048008, 133.872638, 151.7956213, 166.6968482, 179.7665923, 192.1297806, 206.3434408, 218.3471244, 227.2674854, 239.7796944, 248.7332796, 259.6452983, 269.1084859, 275.6368377, 289.4304341, 297.3924417, 299.8717831, 306.0736893, 309.6190404, 311.7924765, 322.7996328, 327.2255881, 330, 333, 336, 340, 343.8195948, 350.5743803, 354.6932855, 359.8551395, 369.262719, 369.2639725, 374.1844014, 380, 386.0538307, 387.2602063, 390.5443925, 395.7093406, 396, 397.6030717, 400.9698217, 401.2251049, 403.8197172, 405.9291415, 408.9701255, 410.7034496, 411.9318252, 413.5936371, 418.304923, 419.6185076, 420.6045785, 421.4090824, 429.9161315, 431.1514575, 431.6159429, 433.9059421, 442.5286755, 444.6939488, 445, 446, 447, 448, 450.3213545, 450.6800788, 451.9782217, 454.2137584, 454.4862931, 454.6300545, 457.0832198, 457.3980337, 459.3454493, 459.9314953, 460.7255431, 460.8821003, 460.8995425, 461.2758248, 461.8202676, 461.9016134, 462.546356, 462.5798325, 463.0389677, 464.0428959, 464.274447, 465.0494162, 466.7468839, 467.2431805, 467.4910634, 468.3042783, 471.983534, 472.6088808, 472.6932945, 472.8328221, 473.0079365, 473.1654939, 473.2195891, 473.7468827, 473.7720767, 473.9644487, 474.0682821, 474.7318693, 474.8987399, 474.9543478, 475.7045688, 476.2773108, 477.5966659, 477.6274885, 478.364265, 478.5191378, 478.6287496, 480.1212576, -459.0739576, -458.6959714, -458.685522, -458.2233292, -457.2678111, -457.1518425, -456.785256, -456.5742553, -455.6465175, -455.5062262, -455.1917218, -454.9737312, -454.7668254, -454.312748, -454.240424, -454.055833, -453.977114, -453.5759265, -452.9348494, -452.6218913, -450.9803157, -449.7786617, -448.7914103, -447.8259354, -447.3508111, -446.2452131, -444.8783059, -444.4781873, -444.198031, -441.2627607, -437.9419174, -437.849072, -437.702201, -437, -435.9006343, -433.1704498, -432.5079364, -432.4848539, -431.3849799, -428.4726815, -420, -417.2948389, -415.7552026, -415.491584, -414.2317288, -413.6609506, -413.4396434, -412.6553946, -411.6090215, -410.265008, -409.0935429, -408.8430346, -408.6134082, -408.3244937, -406.2436284, -404.3248084, -403.8453273, -403.8062703, -398.4094105, -397.8603345, -397.3850317, -396.6216562, -394.6427349, -390.2265823, -390.1622144, -389.986516, -388, -386.0040308, -384.6961707, -383.2372038, -380.9454867, -377.205385, -376.92833, -373.5360427, -370.7155583, -367.8102508, -367.6963996, -363.6788325, -359.9053792, -356.2897295, -354.7468902, -353.5751781, -348.0021818, -340.7690642, -340.7556413, -335.779254, -330.8549398, -328.8961727, -324.6820824, -321.8847844, -318.2599651, -311.7998411, -306.4623091, -300.8708008, -295.7674915, -290.1180858, -284.9524082, -279.9589191, -271.9755388, -265.2378148, -257.1946431, -250.3122476, -245.7627559, -233.1523664, -223.6919013, -215.465067, -202.342361, -191.4866051, -176.7411072, -165.1315277, -150.7781407, -133.2907813, -114.859842, -91.57531844, -67.34117398, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//16 até 242

            try
            {
                byte[] translated = new byte[17];
                intelData = intelData.Replace('.', ',');
                if (intelData.Equals("", StringComparison.InvariantCulture)) return null;
                string[] splitData = intelData.Split(new Char[] { ' ' });
                int j = 0;
                int k = 0;
                int l = 0;
                translated[j] = 0xfe; j++;
                translated[j] = 0; j++;
                translated[j] = 0x22; j++;

                for (int i = 0; i < 5; i++)
                {
                    float f = float.Parse(splitData[2 * i]);
                    float diff = 10000000;
                    int indexer = 0;
                    for (k = 0; k < SpeedLeft.Length; k++)
                    {
                        if (Math.Abs(SpeedLeft[k] - f) < diff)
                        {
                            diff = Math.Abs((float)SpeedLeft[k] - f);
                            indexer = k;
                        }
                    }
                    f = float.Parse(splitData[2 * i + 1]);
                    for (l = 0; l < SpeedLeft.Length; l++)
                    {
                        if (Math.Abs(SpeedLeft[l] - f) < diff)
                        {
                            diff = Math.Abs((float)SpeedRight[l] - f);
                            indexer = l;
                        }
                    }
                    translated[j] = (byte)k; j++;
                    translated[j] = (byte)l; j++;

                }
                //translated[j] = 55;
                return translated;
            }
            catch (IndexOutOfRangeException)
            {
                return null;
            }
            //  foreach (byte b in translated)
            //     Console.Write(b.ToString() + " ");
            //  Console.WriteLine();
            //  Console.WriteLine(intelData);


        }
        public static byte[] TranslateProtocol(string intelData, bool realTransmitter)
        {
            //byte[] translated;
            // Protocolo para o robô
            #region realTransmitter
            if (realTransmitter)
            {
                try
                {
                    byte[] translated = new byte[39];
                    intelData = intelData.Replace('.', ',');
                    if (intelData.Equals("", StringComparison.InvariantCulture)) return null;
                    string[] splitData = intelData.Split(new Char[] { ' ' });
                    //splitData.
                    //translated = new byte[38];
                    int j = 0;
                    translated[j] = 0xfe; j++;
                    translated[j] = 0; j++;
                    translated[j] = 44; j++;
                    for (int i = 0; i < 5; i++)
                    {

                        translated[j] = (byte)(i + 1); j++;
                        /*translated[j] = ScaleVelocity(float.Parse(splitData[6 * i + 1]), 0, wheelVelocity); j++;
                        translated[j] = ScaleVelocity(float.Parse(splitData[6 * i + 2]), 0, wheelVelocity); j++;
                        translated[j] = ScaleVelocity(float.Parse(splitData[6 * i + 3]), 0, wheelVelocity); j++;
                        translated[j] = ScaleVelocity(float.Parse(splitData[6 * i]), 0, wheelVelocity); j++;                        
                        translated[j] = ScaleVelocity(float.Parse(splitData[6 * i + 4]), 0, dribblerVelocity); j++;
                        translated[j] = (byte)(254 * float.Parse(splitData[6 * i + 5])); j++; //kicker
         
                         */
                        /*
                        translated[j] = (byte)float.Parse(splitData[6 * i + 1]); j++;
                        translated[j] = (byte)float.Parse(splitData[6 * i + 2]); j++;
                        translated[j] = (byte)float.Parse(splitData[6 * i + 3]); j++;
                        translated[j] = (byte)float.Parse(splitData[6 * i]); j++;
                        translated[j] = (byte)float.Parse(splitData[6 * i + 4]); j++;
                        translated[j] = (byte)float.Parse(splitData[6 * i + 5]); j++; //kick
                        */
                        float f = float.Parse(splitData[6 * i + 1]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++;
                        f = float.Parse(splitData[6 * i + 2]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++; f = float.Parse(splitData[6 * i + 3]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++; f = float.Parse(splitData[6 * i]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++; f = float.Parse(splitData[6 * i + 4]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++; f = float.Parse(splitData[6 * i + 5]);
                        if (f > 12.7) f = (float)12.7; if (f < -12.7) f = (float)-12.7;
                        translated[j] = (byte)(10 * f);
                        j++;
                    }
                    translated[j] = 55;
                    return translated;
                }
                catch (IndexOutOfRangeException)
                {
                    return null;
                }
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
                byte[] translated;
                string appendString = "15 0 1 ";
                intelData = string.Concat(appendString, intelData);
                translated = Encoding.ASCII.GetBytes(intelData);
                return translated;
            }
            #endregion

        }
        /*        
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
                }*/
    }
}
