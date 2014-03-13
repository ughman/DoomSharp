using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class VariableExpression : Expression
    {
        private string variablename;

        public VariableExpression(string variablename)
        {
            if (variablename == null)
                throw new ArgumentNullException("variablename");
            this.variablename = variablename;
        }

        public override Type Evaluate(CodeContext c)
        {
            LocalBuilder local;
            int parameter;
            if (c.Locals.TryGetValue(variablename,out local))
            {
                c.IL.Emit(OpCodes.Ldloc,local);
                return local.LocalType;
            }
            else if (c.Parameters.TryGetValue(variablename,out parameter))
            {
                if (c.Method.IsStatic)
                {
                    c.IL.Emit(OpCodes.Ldarg,parameter);
                }
                else
                {
                    c.IL.Emit(OpCodes.Ldarg,parameter + 1);
                }
                return c.ParameterTypes[parameter];
            }
            else
            {
                throw new ApplicationException();
            }
        }

        public override void Assign(CodeContext c,Expression source)
        {
            LocalBuilder local;
            int parameter;
            if (c.Locals.TryGetValue(variablename,out local))
            {
                Type type = source.Evaluate(c);
                if (!local.LocalType.IsAssignableFrom(type))
                {
                    throw new ApplicationException();
                }
                c.IL.Emit(OpCodes.Stloc,local);
            }
            else if (c.Parameters.TryGetValue(variablename,out parameter))
            {
                Type type = source.Evaluate(c);
                if (!c.ParameterTypes[parameter].IsAssignableFrom(type))
                {
                    throw new ApplicationException();
                }
                if (c.Method.IsStatic)
                {
                    c.IL.Emit(OpCodes.Starg,parameter);
                }
                else
                {
                    c.IL.Emit(OpCodes.Starg,parameter + 1);
                }
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
