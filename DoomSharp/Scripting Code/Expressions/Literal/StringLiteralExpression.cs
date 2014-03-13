using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class StringLiteralExpression : Expression
    {
        private string value;

        public StringLiteralExpression(string value)
        {
            if (value == null)
                throw new ArgumentNullException("value");
            this.value = value;
        }

        public override Type Evaluate(CodeContext c)
        {
            c.IL.Emit(OpCodes.Ldstr,value);
            return typeof(string);
        }
    }
}
