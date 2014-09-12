using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Thing
    {
        private World world;
        protected abstract Fixed x { get; set; }
        protected abstract Fixed y { get; set; }
        protected abstract int angle { get; set; }
        protected abstract int doomednum { get; set; }

        public Thing(World world)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
            // TODO :: x
            // TODO :: y
            // TODO :: angle
            // TODO :: doomednum
        }

        public World World
        {
            get { return world; }
        }

        public Fixed X
        {
            get { return x; }
            set { x = value; }
        }

        public Fixed Y
        {
            get { return y; }
            set { y = value; }
        }

        public int Angle
        {
            get { return angle; }
            set { angle = value; }
        }

        public int DoomedNum
        {
            get { return doomednum; }
            set { doomednum = value; }
        }
    }
}
