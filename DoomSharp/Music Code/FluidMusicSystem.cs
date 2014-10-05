using System;
using FluidSynthWrapper;

namespace DoomSharp
{
    [CoreSystem("music","fluid","FluidSynth")]
    public sealed class FluidMusicSystem : IMusicSystem
    {
        private Synthesizer synth;
        private AudioDriver driver;

        public FluidMusicSystem()
        {
            Settings settings = new Settings();
            this.synth = new Synthesizer(settings);
            this.driver = new AudioDriver(settings,synth);
            synth.SFontLoad("sndfont2.sf2");
        }

        public void NoteOn(int channel,int note,int velocity)
        {
            synth.NoteOn(channel,(short)note,(short)velocity);
        }

        public void NoteOff(int channel,int note,int velocity)
        {
            synth.NoteOff(channel,(short)note);
        }

        public void PitchBend(int channel,int value)
        {
            synth.PitchBend(channel,(short)value);
        }

        public void ProgramChange(int channel,int program)
        {
            synth.ProgChange(channel,program);
        }

        public void Reset()
        {
            synth.Reset();
        }

        public void Dispose()
        {
            driver.Dispose();
            synth.Dispose();
        }
    }
}
