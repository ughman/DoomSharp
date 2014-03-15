using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Sector
    {
        private World world;
        // TODO :: floorz
        // TODO :: ceilingz
        // TODO :: lightlevel
        // TODO :: special
        // TODO :: tag

        public Sector(World world)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
            // TODO :: floorz
            // TODO :: ceilingz
            // TODO :: lightlevel
            // TODO :: special
            // TODO :: tag
        }

        public World World
        {
            get { return world; }
        }

        public abstract Fixed FloorZ
        {
            get;
            set;
        }

        public abstract Fixed CeilingZ
        {
            get;
            set;
        }

        public abstract int LightLevel
        {
            get;
            set;
        }

        public abstract int Special
        {
            get;
            set;
        }

        public abstract int Tag
        {
            get;
            set;
        }
    }
}
