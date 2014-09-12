using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Sidedef
    {
        private World world;
        protected abstract Sector sector { get; set; }
        protected abstract Fixed xoffset { get; set; }
        protected abstract Fixed yoffset { get; set; }

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

        public Sector Sector
        {
            get { return sector; }
        }

        public Fixed XOffset
        {
            get { return xoffset; }
            set { xoffset = value; }
        }

        public Fixed YOffset
        {
            get { return yoffset; }
            set { yoffset = value; }
        }
    }
}
