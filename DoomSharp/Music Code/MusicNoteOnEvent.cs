using System;

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

        public override void Play(IMusicSystem music)
        {
            music.NoteOn(MIDIChannel,note,volume ?? 127);
        }
    }
}
