using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public abstract class BinaryExpression : Expression
    {
        private Expression left;
        private Expression right;

        public BinaryExpression(Expression left,Expression right)
        {
            if (left == null)
                throw new ArgumentNullException("left");
            if (right == null)
                throw new ArgumentNullException("right");
            this.left = left;
            this.right = right;
        }

        protected Expression Left
        {
            get { return left; }
        }

        protected Expression Right
        {
            get { return right; }
        }
    }
}
