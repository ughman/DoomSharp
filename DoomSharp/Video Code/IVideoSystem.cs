using System;

namespace DoomSharp
{
    public interface IVideoSystem : IDisposable
    {
        void SubmitFrame(IntPtr frame);
        void SubmitPalette(IntPtr palette);
        void Run();
        void ForceRender();
    }
}
