using System;

namespace DoomSharp
{
    public abstract class Linedef
    {
        // TODO :: start
        // TODO :: end
        // TODO :: front
        // TODO :: back
        // TODO :: special
        // TODO :: tag

        public Linedef(Vertex start,Vertex end,Sidedef front,Sidedef back)
        {
            if (start == null)
                throw new ArgumentNullException("start");
            if (end == null)
                throw new ArgumentNullException("end");
            // Sidedefs may be null, so don't check them
            // TODO :: start
            // TODO :: end
            // TODO :: front
            // TODO :: back
            // TODO :: special
            // TODO :: tag
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
