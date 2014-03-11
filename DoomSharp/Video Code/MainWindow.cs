using System;
using System.Drawing;
using System.Runtime.InteropServices;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace DoomSharp
{
    public class MainWindow : GameWindow
    {
        private byte[] display;
        private byte[] palette;

        public MainWindow(bool fullscreen) : base(fullscreen ? DisplayDevice.Default.Width : 800,fullscreen ? DisplayDevice.Default.Height : 600,GraphicsMode.Default,"DoomSharp",fullscreen ? GameWindowFlags.Fullscreen : GameWindowFlags.Default)
        {
            this.display = new byte [320 * 200];
            this.palette = new byte [256 * 3];
            CursorVisible = false;
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);
            MakeCurrent();
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0,320,200,0,-1,1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            GL.Enable(EnableCap.Texture2D);
            byte[] rgbdisplay = new byte [512 * 256 * 3];
            for (int y = 0;y < 200;y++)
            {
                for (int x = 0;x < 320;x++)
                {
                    byte color = display[x + y * 320];
                    rgbdisplay[(x + y * 512) * 3 + 0] = palette[color * 3 + 0];
                    rgbdisplay[(x + y * 512) * 3 + 1] = palette[color * 3 + 1];
                    rgbdisplay[(x + y * 512) * 3 + 2] = palette[color * 3 + 2];
                }
            }
            GL.TexImage2D<byte>(TextureTarget.Texture2D,0,PixelInternalFormat.Rgb,512,256,0,PixelFormat.Rgb,PixelType.UnsignedByte,rgbdisplay);
            GL.TexParameter(TextureTarget.Texture2D,TextureParameterName.TextureMinFilter,(int)TextureMinFilter.Nearest);
            GL.TexParameter(TextureTarget.Texture2D,TextureParameterName.TextureMagFilter,(int)TextureMagFilter.Nearest);
            double x2 = 320.0 / 512.0;
            double y2 = 200.0 / 256.0;
            GL.Begin(PrimitiveType.Quads);
            GL.TexCoord2(0,0);
            GL.Vertex2(0,0);
            GL.TexCoord2(0,y2);
            GL.Vertex2(0,200);
            GL.TexCoord2(x2,y2);
            GL.Vertex2(320,200);
            GL.TexCoord2(x2,0);
            GL.Vertex2(320,0);
            GL.End();
            GL.Disable(EnableCap.Texture2D);
            SwapBuffers();
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

        public void SubmitFrame(IntPtr frame)
        {
            Marshal.Copy(frame,display,0,display.Length);
        }

        public void SubmitPalette(IntPtr palette)
        {
            Marshal.Copy(palette,this.palette,0,this.palette.Length);
        }

        public void ForceRender()
        {
            OnRenderFrame(null);
        }
    }
}
