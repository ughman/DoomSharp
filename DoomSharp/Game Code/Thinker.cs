using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Thinker
    {
        private World world;

        public Thinker(World world)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
        }

        public World World
        {
            get { return world; }
        }

        public abstract bool Tick();
    }
}
