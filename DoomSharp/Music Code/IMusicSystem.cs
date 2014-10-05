using System;

namespace DoomSharp
{
    public interface IMusicSystem : IDisposable
    {
        void NoteOn(int channel,int note,int velocity);
        void NoteOff(int channel,int note,int velocity);
        void PitchBend(int channel,int value);
        void ProgramChange(int channel,int program);
        void Reset();
    }
}
