using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Class,AllowMultiple = true,Inherited = false)]
    public sealed class DoomedNumAttribute : Attribute
    {
        private int value;

        public DoomedNumAttribute(int value)
        {
            this.value = value;
        }

        public int Value
        {
            get { return value; }
        }
    }
}
