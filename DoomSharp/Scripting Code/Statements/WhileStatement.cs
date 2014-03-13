using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class WhileStatement : Statement
    {
        private Expression condition;
        private Statement loopstatement;
        private Statement elsestatement;

        public WhileStatement(Expression condition,Statement loopstatement,Statement elsestatement)
        {
            if (condition == null)
                throw new ArgumentNullException("condition");
            if (loopstatement == null)
                throw new ArgumentNullException("loopstatement");
            if (elsestatement == null)
                throw new ArgumentNullException("elsestatement");
            this.condition = condition;
            this.loopstatement = loopstatement;
            this.elsestatement = elsestatement;
        }

        public override void Compile(CodeContext c)
        {
            Label looplabel = c.IL.DefineLabel();
            Label elselabel = c.IL.DefineLabel();
            Label endlabel = c.IL.DefineLabel();
            c.IL.MarkLabel(looplabel);
            Type type = condition.Evaluate(c);
            if (type != typeof(bool))
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Brfalse,elselabel);
            loopstatement.SubCompile(c);
            c.IL.Emit(OpCodes.Br,looplabel);
            c.IL.MarkLabel(elselabel);
            elsestatement.SubCompile(c);
            c.IL.MarkLabel(endlabel);
        }
    }
}
