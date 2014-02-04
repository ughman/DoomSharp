namespace DoomSharp
{
    public struct Fixed
    {
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
    }
}
