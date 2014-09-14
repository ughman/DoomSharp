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
            Label shortcircuit = c.IL.DefineLabel();
            Type lefttype = Left.Evaluate(c);
            c.IL.Emit(OpCodes.Dup);
            c.IL.Emit(OpCodes.Brtrue,shortcircuit);
            Type righttype = Right.Evaluate(c);
            if (lefttype != typeof(bool) || righttype != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Or);
            c.IL.MarkLabel(shortcircuit);
            return typeof(bool);
        }
    }
}
