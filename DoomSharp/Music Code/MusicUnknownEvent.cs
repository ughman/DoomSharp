using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    public sealed class MusicUnknownEvent : MusicEvent
    {
        public MusicUnknownEvent(int channel,int delay) : base(channel,delay)
        {
        }

        public override void Play(Synthesizer synth)
        {
        }
    }
}
