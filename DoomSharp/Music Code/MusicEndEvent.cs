using System;

namespace DoomSharp
{
    public sealed class MusicEndEvent : MusicEvent
    {
        public MusicEndEvent(int channel,int delay) : base(channel,delay)
        {
        }

        public override bool IsEndEvent
        {
            get { return true; }
        }

        public override void Play(IMusicSystem music)
        {
            music.Reset();
        }
    }
}
