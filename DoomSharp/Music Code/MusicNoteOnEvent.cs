using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    public sealed class MusicNoteOnEvent : MusicEvent
    {
        private int note;
        private int? volume;

        public MusicNoteOnEvent(int note,int? volume,int channel,int delay) : base(channel,delay)
        {
            if (note < 0 || note >= 128)
                throw new ArgumentOutOfRangeException("note");
            if (volume.HasValue && (volume.Value < 0 || volume.Value > 127))
                throw new ArgumentOutOfRangeException("volume");
            this.note = note;
            this.volume = volume;
        }

        public int Note
        {
            get { return note; }
        }

        public int? Volume
        {
            get { return volume; }
        }

        public override void Play(Synthesizer synth)
        {
            synth.NoteOn(MIDIChannel,(short)note,volume.HasValue ? (short)volume.Value : (short)127);
        }
    }
}
