using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    public sealed class MusicPlayer : IMusicSystem
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
            try
            {
                byte[] data = Core.Archives[Core.Archives.Find(name)].Read();
                MusicTrack track = new MusicTrack(data);
                Stop();
                this.track = track;
                this.looping = looping;
                position = 0;
                duration = 0;
            }
            catch (LumpNotFoundException)
            {
                Core.Console.LogError("The music track '{0}' could not be found.",name);
            }
            catch (ApplicationException)
            {
                Core.Console.LogError("An error occurred while trying to play the music track '{0}'.",name);
            }
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
                musicevent.Play(this);
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

        void IMusicSystem.NoteOn(int channel,int note,int velocity)
        {
            synth.NoteOn(channel,(short)note,(short)velocity);
        }

        void IMusicSystem.NoteOff(int channel,int velocity)
        {
            synth.NoteOff(channel,(short)velocity);
        }

        void IMusicSystem.PitchBend(int channel,int value)
        {
            synth.PitchBend(channel,(short)value);
        }

        void IMusicSystem.ProgramChange(int channel,int program)
        {
            synth.ProgChange(channel,program);
        }

        void IMusicSystem.Reset()
        {
            synth.Reset();
        }

        void IDisposable.Dispose()
        {
        }
    }
}
