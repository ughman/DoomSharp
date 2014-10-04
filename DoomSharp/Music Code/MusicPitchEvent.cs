using System;

namespace DoomSharp
{
    public sealed class MusicPitchEvent : MusicEvent
    {
        private int value;

        public MusicPitchEvent(int value,int channel,int delay) : base(channel,delay)
        {
            if (value < 0 || value >= 256)
                throw new ArgumentOutOfRangeException("value");
            this.value = value;
        }

        public int Value
        {
            get { return value; }
        }

        public override void Play(IMusicSystem music)
        {
            music.PitchBend(MIDIChannel,value << 6);
        }
    }
}
