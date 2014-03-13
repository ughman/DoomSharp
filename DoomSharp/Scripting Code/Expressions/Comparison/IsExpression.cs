using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public class IsExpression : BinaryExpression
    {
        public IsExpression(Expression left,Expression right) : base(left,right)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type lefttype = Left.Evaluate(c);
            Type righttype = Right.Evaluate(c);
            if (lefttype != null && lefttype.IsValueType)
            {
                throw new ApplicationException();
            }
            if (righttype != null && righttype.IsValueType)
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Ceq);
            return typeof(bool);
        }
    }
}
