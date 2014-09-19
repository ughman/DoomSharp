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
            else if (variablename == "$activator")
            {
                if (!typeof(ScriptSpecialEnvironment).IsAssignableFrom(c.ParameterTypes[0]))
                    throw new ApplicationException();
                c.IL.Emit(OpCodes.Callvirt,typeof(ScriptSpecialEnvironment).GetProperty("Activator").GetGetMethod());
                return typeof(Actor);
            }
            else if (variablename == "$linedef")
            {
                if (!typeof(ScriptLinedefSpecialEnvironment).IsAssignableFrom(c.ParameterTypes[0]))
                    throw new ApplicationException();
                c.IL.Emit(OpCodes.Callvirt,typeof(ScriptLinedefSpecialEnvironment).GetProperty("Linedef").GetGetMethod());
                return typeof(Linedef);
            }
            else if (variablename == "$isbackside")
            {
                if (!typeof(ScriptLinedefSpecialEnvironment).IsAssignableFrom(c.ParameterTypes[0]))
                    throw new ApplicationException();
                c.IL.Emit(OpCodes.Callvirt,typeof(ScriptLinedefSpecialEnvironment).GetProperty("IsBackSide").GetGetMethod());
                return typeof(bool);
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
