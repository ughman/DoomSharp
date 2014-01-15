using System;

namespace DoomSharp
{
    public class PacketEventArgs : EventArgs
    {
        private PacketType type;
        private byte[] data;

        public PacketType Type
        {
            get { return type; }
            set { type = value; }
        }

        public byte[] Data
        {
            get { return data; }
            set { data = value; }
        }
    }
}
