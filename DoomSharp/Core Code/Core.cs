using System;
using System.Diagnostics;
using System.Collections.Generic;
using OpenTK;
using OpenTK.Input;

namespace DoomSharp
{
    public static class Core
    {
        private static DoomConsole console;
        private static IVideoSystem video;
        private static MusicPlayer music;
        private static MultiArchive archives;
        private static GameState topstate;
        private static Stopwatch stopwatch;
        private static int lasttime;
        private static Dictionary<string,Type> coresystems;

        static Core()
        {
            console = new DoomConsole();
            video = new NullVideoSystem(false);
            music = new MusicPlayer();
            archives = new MultiArchive();
            topstate = null;
            stopwatch = Stopwatch.StartNew();
            lasttime = 0;
            coresystems = new Dictionary<string,Type>();
            PushState(new RootState());
        }

        public static DoomConsole Console
        {
            get { return console; }
        }

        public static IVideoSystem Video
        {
            get { return video; }
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
            if (state == null)
                throw new ArgumentNullException("state");
            state.Push(ref topstate);
        }

        public static void PopState()
        {
            if (topstate is RootState)
                throw new InvalidOperationException();
            topstate = topstate.Next;
        }

        public static void ChangeVideoSystem(string name,bool fullscreen)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            Type type;
            if (!coresystems.TryGetValue("video_" + name,out type))
            {
                console.LogError("There is no video system named '{0}'.",name);
                return;
            }
            // cast to avoid calling (type,bool) overload
            IVideoSystem newvideo = (IVideoSystem)Activator.CreateInstance(type,(object)fullscreen);
            video.Dispose();
            video = newvideo;
            console.LogInfo("Switched to video system '{0}'.",name);
        }

        [RegistrarTypeHandler]
        private static void RegisterType(Type type)
        {
            foreach (CoreSystemAttribute attribute in type.GetCustomAttributes(typeof(CoreSystemAttribute),false))
            {
                coresystems.Add(attribute.Type + "_" + attribute.Name,type);
            }
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
