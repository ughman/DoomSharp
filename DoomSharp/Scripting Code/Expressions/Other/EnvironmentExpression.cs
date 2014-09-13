using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class EnvironmentExpression : Expression
    {
        private string variablename;

        public EnvironmentExpression(string variablename)
        {
            if (variablename == null)
                throw new ArgumentNullException("variablename");
            this.variablename = variablename;
        }

        public override Type Evaluate(CodeContext c)
        {
            if (c.ParameterTypes.Count == 0)
            {
                throw new ApplicationException();
            }
            c.IL.Emit(OpCodes.Ldarg_0);
            if (variablename == "$world")
            {
                if (!typeof(ScriptEnvironment).IsAssignableFrom(c.ParameterTypes[0]))
                    throw new ApplicationException();
                c.IL.Emit(OpCodes.Callvirt,typeof(ScriptEnvironment).GetProperty("World").GetGetMethod());
                return typeof(World);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
