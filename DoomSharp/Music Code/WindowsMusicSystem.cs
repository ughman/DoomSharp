using System;
using System.Runtime.InteropServices;

namespace DoomSharp
{
    [CoreSystem("music","winmm","Windows MIDI")]
    public sealed class WindowsMusicSystem : IMusicSystem
    {
        [DllImport("winmm")]
        private static extern int midiOutOpen(out IntPtr handle,uint uDeviceId,IntPtr dwCallback,IntPtr dwCallbackInstance,uint dwFlags);

        [DllImport("winmm")]
        private static extern int midiOutClose(IntPtr handle);

        [DllImport("winmm")]
        private static extern int midiOutShortMsg(IntPtr handle,int dwMsg);

        [DllImport("winmm")]
        private static extern int midiOutReset(IntPtr handle);

        private IntPtr handle;

        public WindowsMusicSystem()
        {
            if (midiOutOpen(out handle,0,IntPtr.Zero,IntPtr.Zero,0) != 0)
                throw new ApplicationException();
        }

        public void NoteOn(int channel,int note,int velocity)
        {
            midiOutShortMsg(handle,0x90 | channel | note << 8 | velocity << 16);
        }

        public void NoteOff(int channel,int note,int velocity)
        {
            midiOutShortMsg(handle,0x80 | channel | note << 8 | velocity << 16);
        }

        public void PitchBend(int channel,int value)
        {
            int lowvalue = value & 0x7F;
            int highvalue = (value >> 7) & 0x7F;
            midiOutShortMsg(handle,0xE0 | channel | lowvalue << 8 | highvalue << 16);
        }

        public void ProgramChange(int channel,int program)
        {
            midiOutShortMsg(handle,0xC0 | channel | program << 8);
        }

        public void Reset()
        {
            midiOutReset(handle);
        }

        public void Dispose()
        {
            midiOutClose(handle);
        }
    }
}
