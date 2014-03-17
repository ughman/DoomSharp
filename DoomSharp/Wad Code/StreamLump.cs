using System;
using System.IO;

namespace DoomSharp
{
    public sealed class StreamLump : ILump
    {
        private Stream stream;
        private string name;
        private int length;
        private int offset;
        private WeakReference weakreference;

        public StreamLump(Stream stream,string name)
        {
            if (stream == null)
                throw new ArgumentNullException("stream");
            if (name == null)
                throw new ArgumentNullException("name");
            this.stream = stream;
            this.name = name;
            this.length = (int)stream.Length;
            this.offset = 0;
            this.weakreference = new WeakReference(null);
        }

        public StreamLump(Stream stream,string name,int length,int offset)
        {
            if (stream == null)
                throw new ArgumentNullException("stream");
            if (name == null)
                throw new ArgumentNullException("name");
            if (length < 0)
                throw new ArgumentOutOfRangeException("length");
            if (offset < 0)
                throw new ArgumentOutOfRangeException("offset");
            if (offset + length > stream.Length)
                throw new ArgumentOutOfRangeException("offset+length");
            this.stream = stream;
            this.name = name;
            this.length = length;
            this.offset = offset;
            this.weakreference = new WeakReference(null);
        }

        public string Name
        {
            get { return name; }
        }

        public int Length
        {
            get { return length; }
        }

        public byte[] Read()
        {
            byte[] result = (byte[])weakreference.Target;
            if (result == null)
            {
                result = new byte [length];
                stream.Position = offset;
                stream.Read(result,0,length);
                weakreference.Target = result;
            }
            return result;
        }
    }
}
