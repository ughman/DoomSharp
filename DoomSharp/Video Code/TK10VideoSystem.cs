using System;
using System.Drawing;
using System.Runtime.InteropServices;
using OpenTK;
using OpenTK.Input;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace DoomSharp
{
    [CoreSystem("video","tk10","OpenTK GL 1.0")]
    public class TK10VideoSystem : TKBaseVideoSystem
    {
        private byte[] display;
        private byte[] palette;
        private byte[] rgbdisplay;

        public TK10VideoSystem(bool fullscreen) : base(fullscreen)
        {
            this.display = new byte [320 * 200];
            this.palette = new byte [256 * 3];
            this.rgbdisplay = new byte [512 * 256 * 3];
        }

        protected override void OnRenderFrame_Init()
        {
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0,320,200,0,-1,1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            GL.Enable(EnableCap.Texture2D);
            GL.TexParameter(TextureTarget.Texture2D,TextureParameterName.TextureMinFilter,(int)TextureMinFilter.Nearest);
            GL.TexParameter(TextureTarget.Texture2D,TextureParameterName.TextureMagFilter,(int)TextureMagFilter.Nearest);
        }

        protected override void OnRenderFrame_Frame()
        {
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
        }

        public override void SubmitFrame(IntPtr frame)
        {
            Marshal.Copy(frame,display,0,display.Length);
        }

        public override void SubmitPalette(IntPtr palette)
        {
            Marshal.Copy(palette,this.palette,0,this.palette.Length);
        }
    }
}
