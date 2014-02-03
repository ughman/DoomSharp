using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Class,Inherited = false)]
    public sealed class ActorTypeAttribute : Attribute
    {
        private int value;

        public ActorTypeAttribute(int value)
        {
            this.value = value;
        }

        public int Value
        {
            get { return value; }
        }
    }
}
