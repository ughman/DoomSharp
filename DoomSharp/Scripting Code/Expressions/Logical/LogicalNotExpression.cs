using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class LogicalNotExpression : UnaryExpression
    {
        public LogicalNotExpression(Expression inner) : base(inner)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type type = Inner.Evaluate(c);
            if (type != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Ldc_I4_0);
            c.IL.Emit(OpCodes.Ceq);
            return typeof(bool);
        }
    }
}
