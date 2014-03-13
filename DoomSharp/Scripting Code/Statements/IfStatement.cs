using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class IfStatement : Statement
    {
        private Expression condition;
        private Statement thenstatement;
        private Statement elsestatement;

        public IfStatement(Expression condition,Statement thenstatement,Statement elsestatement)
        {
            if (condition == null)
                throw new ArgumentNullException("condition");
            if (thenstatement == null)
                throw new ArgumentNullException("thenstatement");
            if (elsestatement == null)
                throw new ArgumentNullException("elsestatement");
            this.condition = condition;
            this.thenstatement = thenstatement;
            this.elsestatement = elsestatement;
        }

        public override void Compile(CodeContext c)
        {
            Label elselabel = c.IL.DefineLabel();
            Label endlabel = c.IL.DefineLabel();
            Type type = condition.Evaluate(c);
            if (type != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Brfalse,elselabel);
            thenstatement.SubCompile(c);
            c.IL.Emit(OpCodes.Br,endlabel);
            c.IL.MarkLabel(elselabel);
            elsestatement.SubCompile(c);
            c.IL.MarkLabel(endlabel);
        }
    }
}
