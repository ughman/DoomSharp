using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class BitwiseNotExpression : UnaryExpression
    {
        public BitwiseNotExpression(Expression inner) : base(inner)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type type = Inner.Evaluate(c);
            if (type != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Not);
            return typeof(bool);
        }
    }
}
