using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class FalseExpression : Expression
    {
        public override Type Evaluate(CodeContext c)
        {
            c.IL.Emit(OpCodes.Ldc_I4_0);
            return typeof(bool);
        }
    }
}
