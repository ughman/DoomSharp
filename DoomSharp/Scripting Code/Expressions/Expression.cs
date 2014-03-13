using System;

namespace DoomSharp
{
    public abstract class Expression
    {
        public abstract Type Evaluate(CodeContext c);

        public virtual void Execute(CodeContext c)
        {
            throw new ApplicationException();
        }

        public virtual void Assign(CodeContext c,Expression source)
        {
            throw new ApplicationException();
        }

        public virtual Type Invoke(CodeContext c,Expression[] arguments)
        {
            throw new ApplicationException();
        }
    }
}
