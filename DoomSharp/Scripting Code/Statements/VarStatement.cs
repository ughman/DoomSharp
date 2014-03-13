using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class VarStatement : Statement
    {
        private string variablename;
        private Expression expression;

        public VarStatement(string variablename,Expression expression)
        {
            if (variablename == null)
                throw new ArgumentNullException("variablename");
            if (expression == null)
                throw new ArgumentNullException("expression");
            this.variablename = variablename;
            this.expression = expression;
        }

        public override void Compile(CodeContext c)
        {
            Type type = expression.Evaluate(c);
            LocalBuilder local = c.IL.DeclareLocal(type);
            c.IL.Emit(OpCodes.Stloc,local);
            c.Locals.Add(variablename,local);
        }
    }
}
