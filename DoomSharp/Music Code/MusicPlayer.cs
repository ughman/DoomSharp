using System;

namespace DoomSharp
{
    public sealed class MusicPlayer
    {
        private IMusicSystem system;
        private MusicTrack track;
        private int position;
        private double duration;
        private bool looping;

        public MusicPlayer()
        {
            this.system = new NullMusicSystem();
            this.track = null;
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
            system.Reset();
        }

        public void Update(double time)
        {
            duration -= time;
            while (track != null && duration <= 0)
            {
                MusicEvent musicevent = track.Score[position++];
                musicevent.Play(system);
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

        internal void ChangeSystem(IMusicSystem newsystem)
        {
            if (newsystem == null)
                throw new ArgumentNullException("newsystem");
            system.Dispose();
            system = newsystem;
            position = 0;
            duration = 0;
        }
    }
}
