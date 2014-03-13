namespace DoomSharp
{
    [Scriptable]
    public abstract class Sector
    {
        // TODO :: floorz
        // TODO :: ceilingz
        // TODO :: lightlevel
        // TODO :: special
        // TODO :: tag

        public Sector()
        {
            // TODO :: floorz
            // TODO :: ceilingz
            // TODO :: lightlevel
            // TODO :: special
            // TODO :: tag
        }

        public abstract Fixed FloorZ
        {
            get;
            set;
        }

        public abstract Fixed CeilingZ
        {
            get;
            set;
        }

        public abstract int LightLevel
        {
            get;
            set;
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
