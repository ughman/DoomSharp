using System;

namespace DoomSharp
{
    [Scriptable]
    public abstract class Sidedef
    {
        // TODO :: sector
        // TODO :: xoffset
        // TODO :: yoffset

        public Sidedef(Sector sector)
        {
            if (sector == null)
                throw new ArgumentNullException("sector");
            // TODO :: sector
            // TODO :: xoffset
            // TODO :: yoffset
        }

        public abstract Sector Sector
        {
            get;
        }

        public abstract Fixed XOffset
        {
            get;
            set;
        }

        public abstract Fixed YOffset
        {
            get;
            set;
        }
    }
}
