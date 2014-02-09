using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    public sealed class MusicPlayer
    {
        private MusicTrack track;
        private int position;
        private double duration;
        private bool looping;
        private Synthesizer synth;
        private AudioDriver driver;

        public MusicPlayer()
        {
            this.track = null;
            Settings settings = new Settings();
            this.synth = new Synthesizer(settings);
            this.driver = new AudioDriver(settings,synth);
            synth.SFontLoad("sndfont2.sf2");
        }

        public void Play(string name,bool looping)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            byte[] data = Core.Archives[Core.Archives.Find(name)].Read();
            MusicTrack track = new MusicTrack(data);
            Stop();
            this.track = track;
            this.looping = looping;
            position = 0;
            duration = 0;
        }

        public void Stop()
        {
            track = null;
            synth.Reset();
        }

        public void Update(double time)
        {
            duration -= time;
            while (track != null && duration <= 0)
            {
                MusicEvent musicevent = track.Score[position++];
                musicevent.Play(synth);
                duration += musicevent.Delay / 140.0;
                if (musicevent.IsEndEvent || position >= track.Score.Count)
                {
                    if (looping)
                    {
                        position = 0;
                    }
                    else
                    {
                        Stop();
                    }
                }
            }
        }
    }
}
