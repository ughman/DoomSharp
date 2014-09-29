using System;
using System.Drawing;
using System.Runtime.InteropServices;
using OpenTK;
using OpenTK.Input;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace DoomSharp
{
    [CoreSystem("video","null","None")]
    public sealed class NullVideoSystem : IVideoSystem
    {
        public NullVideoSystem(bool fullscreen)
        {
        }

        public void SubmitFrame(IntPtr frame)
        {
        }

        public void SubmitPalette(IntPtr frame)
        {
        }

        public void Run()
        {
            while (true)
            {
                Core.Update();
            }
        }

        public void ForceRender()
        {
        }

        public void Dispose()
        {
        }
    }
}
