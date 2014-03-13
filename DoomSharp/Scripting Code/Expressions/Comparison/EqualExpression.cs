using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public class EqualExpression : BinaryExpression
    {
        public EqualExpression(Expression left,Expression right) : base(left,right)
        {
        }

        public override Type Evaluate(CodeContext c)
        {
            Type lefttype = Left.Evaluate(c);
            Type righttype = Left.Evaluate(c);
            if (lefttype == typeof(int) && righttype == typeof(int))
            {
                c.IL.Emit(OpCodes.Ceq);
            }
            else if (lefttype == typeof(Fixed) && righttype == typeof(Fixed))
            {
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("op_Equality"));
            }
            else if (lefttype == typeof(Fixed) && righttype == typeof(int))
            {
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("FromInt"));
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("op_Equality"));
            }
            else if (lefttype == typeof(int) && righttype == typeof(Fixed))
            {
                c.IL.Emit(OpCodes.Stloc_0);
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("FromInt"));
                c.IL.Emit(OpCodes.Ldloc_0);
                c.IL.Emit(OpCodes.Call,typeof(Fixed).GetMethod("op_Equality"));
            }
            else
            {
                throw new ApplicationException();
            }
            return typeof(bool);
        }
    }
}
