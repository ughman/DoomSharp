using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Linedef
    {
        private World world;
        // TODO :: start
        // TODO :: end
        // TODO :: front
        // TODO :: back
        // TODO :: special
        // TODO :: tag

        public Linedef(World world,Vertex start,Vertex end,Sidedef front,Sidedef back)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            if (start == null)
                throw new ArgumentNullException("start");
            if (end == null)
                throw new ArgumentNullException("end");
            // Sidedefs may be null, so don't check them
            if (start.World != world)
                throw new ArgumentException("Start vertex is from another world.");
            if (end.World != world)
                throw new ArgumentException("End vertex is from another world.");
            if (front != null && front.World != world)
                throw new ArgumentException("Front sidedef is from another world.");
            if (back != null && back.World != world)
                throw new ArgumentException("Back sidedef is from another world.");
            this.world = world;
            // TODO :: start
            // TODO :: end
            // TODO :: front
            // TODO :: back
            // TODO :: special
            // TODO :: tag
        }

        public World World
        {
            get { return world; }
        }

        public abstract Vertex Start
        {
            get;
        }

        public abstract Vertex End
        {
            get;
        }

        public abstract Sidedef Front
        {
            get;
        }

        public abstract Sidedef Back
        {
            get;
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
