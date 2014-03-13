using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public abstract class UnaryExpression : Expression
    {
        private Expression inner;

        public UnaryExpression(Expression inner)
        {
            if (inner == null)
                throw new ArgumentNullException("inner");
            this.inner = inner;
        }

        protected Expression Inner
        {
            get { return inner; }
        }
    }
}
