using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class ModuloExpression : BinaryExpression
    {
        public ModuloExpression(Expression left,Expression right) : base(left,right)
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
            c.IL.Emit(OpCodes.Rem);
            return typeof(int);
        }
    }
}
