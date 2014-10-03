using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Vertex
    {
        private World world;
        protected abstract Fixed x { get; set; }
        protected abstract Fixed y { get; set; }

        public Vertex(World world,Fixed x,Fixed y)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
            // TODO :: x
            // TODO :: y
        }

        public World World
        {
            get { return world; }
        }

        [Scriptable]
        public Fixed X
        {
            get { return x; }
        }

        [Scriptable]
        public Fixed Y
        {
            get { return y; }
        }
    }
}
