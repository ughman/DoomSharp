using System;
using System.Diagnostics;
using OpenTK;
using OpenTK.Input;

namespace DoomSharp
{
    public static class Core
    {
        private static MusicPlayer music;
        private static MultiArchive archives;
        private static GameState topstate;
        private static Stopwatch stopwatch;
        private static int lasttime;

        static Core()
        {
            music = new MusicPlayer();
            archives = new MultiArchive();
            topstate = null;
            stopwatch = Stopwatch.StartNew();
            lasttime = 0;
            PushState(new RootState());
        }

        public static MusicPlayer Music
        {
            get { return music; }
        }

        public static MultiArchive Archives
        {
            get { return archives; }
        }

        public static void Update()
        {
            double time = stopwatch.ElapsedMilliseconds - lasttime;
            lasttime += (int)time;
            time /= 1000;
            music.Update(time);
            topstate.Update(time,true);
            for (GameState state = topstate.Next;state != null;state = state.Next)
            {
                state.Update(time,false);
            }
        }

        public static void KeyDown(Key key)
        {
            topstate.KeyDown(key);
        }

        public static void KeyUp(Key key)
        {
            topstate.KeyUp(key);
        }

        public static void PushState(GameState state)
        {
            state.Push(ref topstate);
        }

        public static void PopState()
        {
            if (topstate is RootState)
                throw new InvalidOperationException();
            topstate = topstate.Next;
        }

        private class RootState : GameState
        {
            public override void Update(double time,bool top)
            {
                if (top)
                {
                    throw new InvalidOperationException();
                }
            }
        }
    }
}
