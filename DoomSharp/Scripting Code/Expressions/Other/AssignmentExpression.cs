using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class AssignmentExpression : BinaryExpression
    {
        public AssignmentExpression(Expression left,Expression right) : base(left,right)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Left.Assign(c,Right);
            return Left.Evaluate(c);
        }

        public override void Execute(CodeContext c)
        {
            Left.Assign(c,Right);
        }
    }
}
