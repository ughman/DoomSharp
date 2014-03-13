using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class CallExpression : UnaryExpression
    {
        private Expression[] arguments;

        public CallExpression(Expression inner,Expression[] arguments) : base(inner)
        {
            if (arguments == null)
                throw new ArgumentNullException("arguments");
            this.arguments = arguments;
        }

        public override Type Evaluate(CodeContext c)
        {
            Type type = Inner.Invoke(c,arguments);
            if (type == typeof(void))
            {
                throw new ApplicationException();
            }
            return type;
        }

        public override void Execute(CodeContext c)
        {
            Type type = Inner.Invoke(c,arguments);
            if (type != typeof(void))
            {
                c.IL.Emit(OpCodes.Pop);
            }
        }
    }
}
