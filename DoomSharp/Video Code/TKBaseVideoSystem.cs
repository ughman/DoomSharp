using System;
using System.Drawing;
using System.Runtime.InteropServices;
using OpenTK;
using OpenTK.Input;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace DoomSharp
{
    public abstract class TKBaseVideoSystem : GameWindow,IVideoSystem
    {
        private bool initialized;

        public TKBaseVideoSystem(bool fullscreen) : base(fullscreen ? DisplayDevice.Default.Width : 800,fullscreen ? DisplayDevice.Default.Height : 600,GraphicsMode.Default,"DoomSharp",fullscreen ? GameWindowFlags.Fullscreen : GameWindowFlags.Default)
        {
            this.initialized = false;
            CursorVisible = false;
            VSync = VSyncMode.Off;
        }

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            base.OnUpdateFrame(e);
            Core.Update();
        }

        protected override void OnResize(System.EventArgs e)
        {
            base.OnResize(e);
            MakeCurrent();
            GL.Viewport(ClientRectangle);
        }

        protected override void OnKeyUp(KeyboardKeyEventArgs e)
        {
            base.OnKeyUp(e);
            Core.KeyUp(e.Key);
        }

        protected override void OnKeyDown(KeyboardKeyEventArgs e)
        {
            base.OnKeyDown(e);
            Core.KeyDown(e.Key);
        }

        public abstract void SubmitFrame(IntPtr frame);
        public abstract void SubmitPalette(IntPtr frame);

        public void ForceRender()
        {
            OnRenderFrame(null);
        }
    }
}
