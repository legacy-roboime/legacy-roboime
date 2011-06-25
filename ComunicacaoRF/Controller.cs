using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

namespace ControleRobo
{
    enum Command
    {
        None, WHEEL1 = 1, WHEEL2 = 2, WHEEL3 = 3, WHEEL4 = 4, DRIBBLER = 5, KICKER = 6
    }

    abstract class Controller
    {
        public int robotId;
        public Command[] issuedCommands;

        public abstract void GetCommandList(object sender, ElapsedEventArgs e);
    }

}
