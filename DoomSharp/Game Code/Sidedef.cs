using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Sidedef
    {
        private World world;
        // TODO :: sector
        // TODO :: xoffset
        // TODO :: yoffset

        public Sidedef(World world,Sector sector)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            if (sector == null)
                throw new ArgumentNullException("sector");
            if (sector.World != world)
                throw new ArgumentException("Sector is from another world.");
            this.world = world;
            // TODO :: sector
            // TODO :: xoffset
            // TODO :: yoffset
        }

        public World World
        {
            get { return world; }
        }

        public abstract Sector Sector
        {
            get;
        }

        public abstract Fixed XOffset
        {
            get;
            set;
        }

        public abstract Fixed YOffset
        {
            get;
            set;
        }
    }
}
