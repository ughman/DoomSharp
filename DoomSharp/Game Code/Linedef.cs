using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Linedef
    {
        private World world;
        protected abstract Vertex start { get; set; }
        protected abstract Vertex end { get; set; }
        protected abstract Sidedef front { get; set; }
        protected abstract Sidedef back { get; set; }
        protected abstract int special { get; set; }
        protected abstract int tag { get; set; }

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

        [Scriptable]
        public Vertex Start
        {
            get { return start; }
        }

        [Scriptable]
        public Vertex End
        {
            get { return end; }
        }

        [Scriptable]
        public Sidedef Front
        {
            get { return front; }
        }

        [Scriptable]
        public Sidedef Back
        {
            get { return back; }
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
