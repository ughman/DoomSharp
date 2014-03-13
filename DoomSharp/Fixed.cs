namespace DoomSharp
{
    public struct Fixed
    {
        public static Fixed Zero
        {
            get { return new Fixed(0); }
        }

        public static Fixed FromInt(int value)
        {
            return new Fixed(value << 16);
        }

        private int value;

        public Fixed(int value)
        {
            this.value = value;
        }

        public int Value
        {
            get { return value; }
        }

        public int IntValue
        {
            get { return value >> 16; }
        }

        public override bool Equals(object obj)
        {
            return obj is Fixed && this == (Fixed)obj;
        }

        public override int GetHashCode()
        {
            return value;
        }

        public static bool operator ==(Fixed left,Fixed right)
        {
            return left.value == right.value;
        }

        public static bool operator !=(Fixed left,Fixed right)
        {
            return left.value != right.value;
        }

        public static bool operator <(Fixed left,Fixed right)
        {
            return left.value < right.value;
        }

        public static bool operator >(Fixed left,Fixed right)
        {
            return left.value > right.value;
        }

        public static Fixed operator -(Fixed f)
        {
            return new Fixed(-f.value);
        }

        public static Fixed operator +(Fixed left,Fixed right)
        {
            return new Fixed(left.value + right.value);
        }

        public static Fixed operator -(Fixed left,Fixed right)
        {
            return new Fixed(left.value - right.value);
        }
    }
}
