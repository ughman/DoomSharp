using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class ExpressionStatement : Statement
    {
        private Expression expression;

        public ExpressionStatement(Expression expression)
        {
            if (expression == null)
                throw new ArgumentNullException("expression");
            this.expression = expression;
        }

        public override void Compile(CodeContext c)
        {
            expression.Execute(c);
        }
    }
}
