using System;

namespace DoomSharp
{
    public sealed class MusicNoteOffEvent : MusicEvent
    {
        private int volume;

        public MusicNoteOffEvent(int volume,int channel,int delay) : base(channel,delay)
        {
            if (volume < 0 || volume >= 128)
                throw new ArgumentOutOfRangeException("volume");
            this.volume = volume;
        }

        public int Volume
        {
            get { return volume; }
        }

        public override void Play(IMusicSystem music)
        {
            music.NoteOff(MIDIChannel,volume);
        }
    }
}
