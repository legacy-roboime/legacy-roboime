using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
//using System.Windows.Forms;

namespace ControleRobo
{
    struct Key
    {
        public Command command;
        public ConsoleKey key;
    }

    class KeyboardController : Controller
    {
        private Key[] controllerKeys;
        private System.Timers.Timer controllerTimer;

        public KeyboardController(int _robotId, ConsoleKey[] key)
        {
            robotId = _robotId;
            issuedCommands = new Command[6];
            controllerKeys = new Key[6];
            for (int i = 0; i < 6; i++)
            {
                controllerKeys[i].key = key[i];
                controllerKeys[i].command = (Command)i+1;
            }
        }

        public void GetCommandList(object sender, ElapsedEventArgs e)
        {
            Command[] commands = new Command[controllerKeys.Length];
            for (int i = 0, j = 0; i < controllerKeys.Length; i++)
            {
                if (IsKeyDown(controllerKeys[i]))
                {
                    commands[j] = controllerKeys[i].command;
                }
                j++;
            }
            issuedCommands = commands;
        }


        public static bool IsKeyDown(Key key1)
        {
            return GetAsyncKeyState((int)key1.key) < 0;
        }

        public void StartReadingInput()
        {
            System.Timers.Timer controllerTimer = new System.Timers.Timer(2);
            controllerTimer.Elapsed += new ElapsedEventHandler(GetCommandList);
            controllerTimer.Enabled = true;
        }


        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern short GetAsyncKeyState(int vkey);


    }
}
