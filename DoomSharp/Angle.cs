namespace DoomSharp
{
    public struct Angle
    {
        public static Angle Deg45
        {
            get { return new Angle(0x20000000); }
        }

        public static Angle Deg90
        {
            get { return new Angle(0x40000000); }
        }

        public static Angle Deg180
        {
            get { return new Angle(0x80000000); }
        }

        public static Angle Deg270
        {
            get { return new Angle(0xC0000000); }
        }

        private uint value;

        public Angle(uint value)
        {
            this.value = value;
        }

        public uint Value
        {
            get { return value; }
        }

        public override bool Equals(object obj)
        {
            return obj is Angle && this == (Angle)obj;
        }

        public override int GetHashCode()
        {
            return (int)value;
        }

        public static bool operator ==(Angle left,Angle right)
        {
            return left.value == right.value;
        }

        public static bool operator !=(Angle left,Angle right)
        {
            return left.value != right.value;
        }

        public static Angle operator +(Angle left,Angle right)
        {
            return new Angle(left.value + right.value);
        }

        public static Angle operator -(Angle left,Angle right)
        {
            return new Angle(left.value - right.value);
        }
    }
}
