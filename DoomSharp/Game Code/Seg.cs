using System;

namespace DoomSharp
{
    public abstract class Seg
    {
        private World world;
        protected abstract Vertex start { get; set; }
        protected abstract Vertex end { get; set; }
        protected abstract Linedef linedef { get; set; }
        private Sidedef front;
        private Sidedef back;
        protected abstract uint angle { get; set; }
        protected abstract Fixed offset { get; set; }

        public Seg(World world,Vertex start,Vertex end,Linedef linedef,bool isbackside,uint angle,Fixed offset)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            if (start == null)
                throw new ArgumentNullException("start");
            if (end == null)
                throw new ArgumentNullException("end");
            if (linedef == null)
                throw new ArgumentNullException("linedef");
            if (start.World != world)
                throw new ArgumentException("Start vertex is from another world.");
            if (end.World != world)
                throw new ArgumentException("End vertex is from another world.");
            if (linedef.World != world)
                throw new ArgumentException("Linedef is from another world.");
            this.world = world;
            // TODO :: start
            // TODO :: end
            // TODO :: linedef
            if (!isbackside)
            {
                this.front = linedef.Front;
                this.back = linedef.Back;
            }
            else
            {
                this.front = linedef.Back;
                this.back = linedef.Front;
            }
            // TODO :: angle
            // TODO :: offset
        }

        public World World
        {
            get { return world; }
        }

        public Vertex Start
        {
            get { return start; }
        }

        public Vertex End
        {
            get { return end; }
        }

        public Linedef Linedef
        {
            get { return linedef; }
        }

        public Sidedef Front
        {
            get { return front; }
        }

        public Sidedef Back
        {
            get { return back; }
        }

        public uint Angle
        {
            get { return angle; }
        }

        public Fixed Offset
        {
            get { return offset; }
        }
    }
}
