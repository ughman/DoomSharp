using System;

namespace DoomSharp
{
    [CoreSystem("music","null","None")]
    public sealed class NullMusicSystem : IMusicSystem
    {
        public void NoteOn(int channel,int note,int velocity)
        {
        }

        public void NoteOff(int channel,int note,int velocity)
        {
        }

        public void PitchBend(int channel,int value)
        {
        }

        public void ProgramChange(int channel,int program)
        {
        }

        public void Reset()
        {
        }

        public void Dispose()
        {
        }
    }
}
