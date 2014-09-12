using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Sector
    {
        private World world;
        protected abstract Fixed floorz { get; set; }
        protected abstract Fixed ceilingz { get; set; }
        protected abstract int lightlevel { get; set; }
        protected abstract int special { get; set; }
        protected abstract int tag { get; set; }

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

        public Fixed FloorZ
        {
            get { return floorz; }
            set { floorz = value; }
        }

        public Fixed CeilingZ
        {
            get { return ceilingz; }
            set { ceilingz = value; }
        }

        public int LightLevel
        {
            get { return lightlevel; }
            set { lightlevel = value; }
        }

        public int Special
        {
            get { return special; }
            set { special = value; }
        }

        public int Tag
        {
            get { return tag; }
            set { tag = value; }
        }
    }
}
