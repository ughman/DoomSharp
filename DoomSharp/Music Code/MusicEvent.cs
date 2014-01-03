using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    public abstract class MusicEvent
    {
        public static MusicEvent Parse(byte[] data,ref int offset)
        {
            if (data == null)
                throw new ArgumentNullException("data");
            if (offset < 0 || offset >= data.Length)
                throw new ArgumentOutOfRangeException("offset");
            if (data.Length < offset + 1)
            {
                throw new ApplicationException();
            }
            byte cmd = data[offset++];
            int channel = cmd & 0xF;
            int evtype = (cmd >> 4) & 7;
            MusicEvent result;
            if (evtype == 0)
            {
                if (data.Length < offset + 1)
                {
                    throw new ApplicationException();
                }
                int note = data[offset++] & 127;
                result = new MusicNoteOffEvent(note,channel,0);
            }
            else if (evtype == 1)
            {
                if (data.Length < offset + 1)
                {
                    throw new ApplicationException();
                }
                int note = data[offset++];
                int? volume = null;
                if ((note & 128) != 0)
                {
                    note &= 127;
                    if (data.Length < offset + 1)
                    {
                        throw new ApplicationException();
                    }
                    volume = data[offset++] & 127;
                }
                result = new MusicNoteOnEvent(note,volume,channel,0);
            }
            else if (evtype == 2)
            {
                if (data.Length < offset + 1)
                {
                    throw new ApplicationException();
                }
                int value = data[offset++];
                result = new MusicPitchEvent(value,channel,0);
            }
            else if (evtype == 3)
            {
                if (data.Length < offset + 1)
                {
                    throw new ApplicationException();
                }
                offset++;
                // TODO
                result = new MusicUnknownEvent(channel,0);
            }
            else if (evtype == 4)
            {
                if (data.Length < offset + 2)
                {
                    throw new ApplicationException();
                }
                int controller = data[offset++] & 127;
                int value = data[offset++] & 127;
                result = new MusicControllerEvent(controller,value,channel,0);
            }
            else if (evtype == 6)
            {
                // TODO
                result = new MusicUnknownEvent(channel,0);
            }
            else
            {
                result = new MusicUnknownEvent(channel,0);
            }
            while ((cmd & 128) != 0)
            {
                if (data.Length < offset + 1)
                {
                    throw new ApplicationException();
                }
                cmd = data[offset++];
                result.delay <<= 7;
                result.delay += cmd & 127;
            }
            return result;
        }

        private int channel;
        private int delay;

        public MusicEvent(int channel,int delay)
        {
            if (channel < 0 || channel > 15)
                throw new ArgumentOutOfRangeException("channel");
            this.channel = channel;
            this.delay = delay;
        }

        public int Channel
        {
            get { return channel; }
        }

        public int MIDIChannel
        {
            get
            {
                if (channel == 15)
                    return 9;
                else if (channel == 9)
                    return 15;
                else
                    return channel;
            }
        }

        public int Delay
        {
            get { return delay; }
        }

        public virtual bool IsEndEvent
        {
            get { return false; }
        }

        public abstract void Play(Synthesizer synth);
    }
}
