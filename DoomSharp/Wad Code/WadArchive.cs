using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace DoomSharp
{
    public sealed class WadArchive : IArchive
    {
        private List<ILump> lumps;

        public WadArchive(Stream stream)
        {
            if (stream == null)
                throw new ArgumentNullException("stream");
            if (stream.Length < 16)
            {
                throw new ApplicationException();
            }
            byte[] buffer = new byte [16];
            stream.Read(buffer,0,12);
            string magic = Encoding.ASCII.GetString(buffer,0,4);
            int lumpcount = BitConv.FromInt32(buffer,4);
            int diroffset = BitConv.FromInt32(buffer,8);
            if (magic != "IWAD" && magic != "PWAD")
            {
                throw new ApplicationException();
            }
            if (lumpcount < 0)
            {
                throw new ApplicationException();
            }
            if (diroffset < 0)
            {
                throw new ApplicationException();
            }
            if (stream.Length < diroffset + lumpcount * 16)
            {
                throw new ApplicationException();
            }
            lumps = new List<ILump>(lumpcount);
            stream.Position = diroffset;
            for (int i = 0;i < lumpcount;i++)
            {
                stream.Read(buffer,0,16);
                int offset = BitConv.FromInt32(buffer,0);
                int length = BitConv.FromInt32(buffer,4);
                string name = Encoding.ASCII.GetString(buffer,8,8);
                if (name.Contains("\0"))
                {
                    name = name.Remove(name.IndexOf('\0'));
                }
                name = name.ToUpper();
                if (offset < 0)
                {
                    throw new ApplicationException();
                }
                if (length < 0)
                {
                    throw new ApplicationException();
                }
                if (stream.Length < offset + length)
                {
                    throw new ApplicationException();
                }
                lumps.Add(new StreamLump(stream,name,length,offset));
            }
        }

        public int LumpCount
        {
            get { return lumps.Count; }
        }

        public ILump this[int i]
        {
            get
            {
                if (i < 0 || i >= lumps.Count)
                    throw new IndexOutOfRangeException();
                return lumps[i];
            }
        }

        public int Find(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            name = name.ToUpper();
            for (int i = 0;i < lumps.Count;i++)
            {
                if (lumps[i].Name == name)
                {
                    return i;
                }
            }
            throw new LumpNotFoundException(name);
        }
    }
}
