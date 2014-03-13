using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class LogicalOrExpression : BinaryExpression
    {
        public LogicalOrExpression(Expression left,Expression right) : base(left,right)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type lefttype = Left.Evaluate(c);
            Type righttype = Left.Evaluate(c);
            if (lefttype != typeof(bool) || righttype != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Or);
            return typeof(bool);
        }
    }
}
