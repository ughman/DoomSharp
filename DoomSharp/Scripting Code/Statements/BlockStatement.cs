using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class BlockStatement : Statement
    {
        private List<Statement> statements;

        public BlockStatement()
        {
            this.statements = new List<Statement>();
        }

        public IList<Statement> Statements
        {
            get { return statements; }
        }

        public override void Compile(CodeContext c)
        {
            foreach (Statement statement in statements)
            {
                statement.Compile(c);
            }
        }
    }
}
