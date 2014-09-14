using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class ReturnStatement : Statement
    {
        private Expression expression;

        public ReturnStatement(Expression expression)
        {
            // expression can be null
            this.expression = expression;
        }

        public override void Compile(CodeContext c)
        {
            if (expression == null)
            {
                if (c.ReturnType != typeof(void))
                {
                    throw new ApplicationException();
                }
                c.IL.Emit(OpCodes.Ret);
            }
            else if (expression != null)
            {
                if (c.ReturnType == typeof(void))
                {
                    throw new ApplicationException();
                }
                Type type = expression.Evaluate(c);
                c.Convert(type,c.ReturnType);
                c.IL.Emit(OpCodes.Ret);
            }
        }
    }
}
