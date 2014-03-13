using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class NullExpression : Expression
    {
        public override Type Evaluate(CodeContext c)
        {
            c.IL.Emit(OpCodes.Ldnull);
            return null;
        }
    }
}
