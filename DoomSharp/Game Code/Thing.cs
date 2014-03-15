using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Thing
    {
        private World world;
        // TODO :: x
        // TODO :: y
        // TODO :: angle
        // TODO :: doomednum

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

        public abstract Fixed X
        {
            get;
            set;
        }

        public abstract Fixed Y
        {
            get;
            set;
        }

        public abstract int Angle
        {
            get;
            set;
        }

        public abstract int DoomedNum
        {
            get;
            set;
        }
    }
}
