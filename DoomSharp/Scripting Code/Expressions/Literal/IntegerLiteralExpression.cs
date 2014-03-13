using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class IntegerLiteralExpression : Expression
    {
        private int value;

        public IntegerLiteralExpression(int value)
        {
            this.value = value;
        }

        public override Type Evaluate(CodeContext c)
        {
            c.IL.Emit(OpCodes.Ldc_I4,value);
            return typeof(int);
        }
    }
}
