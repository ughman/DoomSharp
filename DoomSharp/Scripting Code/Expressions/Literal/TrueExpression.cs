using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class TrueExpression : Expression
    {
        public override Type Evaluate(CodeContext c)
        {
            c.IL.Emit(OpCodes.Ldc_I4_1);
            return typeof(bool);
        }
    }
}
