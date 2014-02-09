using System;
using OpenTK;
using OpenTK.Input;

namespace DoomSharp
{
    public static class Core
    {
        private static MultiArchive archives;
        private static GameState topstate;

        static Core()
        {
            archives = new MultiArchive();
            topstate = null;
            PushState(new RootState());
        }

        public static MultiArchive Archives
        {
            get { return archives; }
        }

        public static void Update(double time)
        {
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
