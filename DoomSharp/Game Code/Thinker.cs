using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Thinker
    {
        private World world;
        private bool active;

        public Thinker(World world)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
            this.active = false;
        }

        public World World
        {
            get { return world; }
        }

        [Scriptable]
        public bool Active
        {
            get { return active; }
        }

        public abstract bool Tick();

        [Scriptable]
        public void Start()
        {
            if (active)
                throw new InvalidOperationException();
            world.AddThinker(this);
            active = true;
        }

        [Scriptable]
        public void Stop()
        {
            if (!active)
                throw new InvalidOperationException();
            world.RemoveThinker(this);
            active = false;
        }
    }
}
