using System;

namespace DoomSharp
{
    public sealed class MusicControllerEvent : MusicEvent
    {
        private int controller;
        private int value;

        public MusicControllerEvent(int controller,int value,int channel,int delay) : base(channel,delay)
        {
            if (controller < 0 || controller >= 128)
                throw new ArgumentOutOfRangeException("controller");
            if (value < 0 || value >= 128)
                throw new ArgumentOutOfRangeException("value");
            this.controller = controller;
            this.value = value;
        }

        public int Controller
        {
            get { return controller; }
        }

        public int Value
        {
            get { return value; }
        }

        public override void Play(IMusicSystem music)
        {
            switch (controller)
            {
                case 0:
                    music.ProgramChange(MIDIChannel,value);
                    break;
            }
        }
    }
}
