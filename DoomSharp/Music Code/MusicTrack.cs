using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class MusicTrack
    {
        public const int Magic = 0x1A53554D;

        private short[] instruments;
        private List<MusicEvent> score;

        public MusicTrack(byte[] data)
        {
            if (data == null)
                throw new ArgumentNullException("data");
            if (data.Length < 16)
            {
                throw new ApplicationException();
            }
            int magic = BitConv.FromInt32(data,0);
            int scorelength = (ushort)BitConv.FromInt16(data,4);
            int scorestart = (ushort)BitConv.FromInt16(data,6);
            int channels = (ushort)BitConv.FromInt16(data,8);
            int secchannels = (ushort)BitConv.FromInt16(data,10);
            int instrumentcount = (ushort)BitConv.FromInt16(data,12);
            int unused = (ushort)BitConv.FromInt16(data,14);
            if (magic != Magic)
            {
                throw new ApplicationException();
            }
            if (scorestart < 16)
            {
                throw new ApplicationException();
            }
            if (scorestart + scorelength != data.Length)
            {
                throw new ApplicationException();
            }
            if (scorestart < 16 + instrumentcount * 2)
            {
                throw new ApplicationException();
            }
            instruments = new short [instrumentcount];
            for (int i = 0;i < instrumentcount;i++)
            {
                instruments[i] = BitConv.FromInt16(data,16 + i * 2);
            }
            score = new List<MusicEvent>();
            int offset = scorestart;
            while (offset != data.Length)
            {
                score.Add(MusicEvent.Parse(data,ref offset));
            }
        }

        public IList<MusicEvent> Score
        {
            get { return score; }
        }

        public short[] Instruments
        {
            get { return instruments; }
        }
    }
}
