namespace DoomSharp
{
    [Scriptable]
    public abstract class Thing
    {
        // TODO :: x
        // TODO :: y
        // TODO :: angle
        // TODO :: doomednum

        public Thing()
        {
            // TODO :: x
            // TODO :: y
            // TODO :: angle
            // TODO :: doomednum
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
