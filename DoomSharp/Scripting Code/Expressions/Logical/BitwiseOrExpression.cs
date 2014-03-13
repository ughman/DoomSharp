using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class BitwiseOrExpression : BinaryExpression
    {
        public BitwiseOrExpression(Expression left,Expression right) : base(left,right)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type lefttype = Left.Evaluate(c);
            Type righttype = Left.Evaluate(c);
            if (lefttype != typeof(int) || righttype != typeof(int))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Or);
            return typeof(int);
        }
    }
}
