using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Method,AllowMultiple = true)]
    public sealed class LinedefSpecialAttribute : Attribute
    {
        private int number;
        private LinedefActivationType activationtype;
        private bool repeatable;

        public LinedefSpecialAttribute(int number)
        {
            this.number = number;
            this.activationtype = LinedefActivationType.None;
            this.repeatable = false;
        }

        public int Number
        {
            get { return number; }
        }

        public LinedefActivationType ActivationType
        {
            get { return activationtype; }
            set { activationtype = value; }
        }

        public bool Repeatable
        {
            get { return repeatable; }
            set { repeatable = value; }
        }
    }
}
