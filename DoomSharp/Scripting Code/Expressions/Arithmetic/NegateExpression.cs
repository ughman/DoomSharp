using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class NegateExpression : UnaryExpression
    {
        public NegateExpression(Expression inner) : base(inner)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type type = Inner.Evaluate(c);
            if (type == typeof(int))
            {
                c.IL.Emit(OpCodes.Neg);
                return typeof(int);
            }
            else if (type == typeof(Fixed))
            {
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("op_UnaryNegation"));
                return typeof(Fixed);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
