using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Vertex
    {
        private World world;
        // TODO :: x
        // TODO :: y

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

        public abstract Fixed X
        {
            get;
        }

        public abstract Fixed Y
        {
            get;
        }
    }
}
