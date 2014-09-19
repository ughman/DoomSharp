using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class LinedefSpecialDefinition : Definition
    {
        private static Type[] parametertypes;

        static LinedefSpecialDefinition()
        {
            parametertypes = new Type [1];
            parametertypes[0] = typeof(ScriptLinedefSpecialEnvironment);
        }

        private Statement statement;
        private List<LinedefSpecialAttribute> attributes;
        private MethodBuilder method;

        public LinedefSpecialDefinition(Statement statement,IEnumerable<LinedefSpecialAttribute> attributes)
        {
            if (statement == null)
                throw new ArgumentNullException("statement");
            if (attributes == null)
                throw new ArgumentNullException("attributes");
            this.statement = statement;
            this.attributes = new List<LinedefSpecialAttribute>(attributes);
            this.method = null;
        }

        public override void DefineMembers(DefinitionContext c)
        {
            if (method != null)
                throw new InvalidOperationException();
            method = c.GlobalType.DefineMethod("LineSpecial",MethodAttributes.Static | MethodAttributes.Public,typeof(bool),parametertypes);
            foreach (LinedefSpecialAttribute attribute in attributes)
            {
                Type attrtype = typeof(LinedefSpecialAttribute);
                Type[] argtypes = new Type [1];
                argtypes[0] = typeof(int);
                ConstructorInfo ctor = attrtype.GetConstructor(argtypes);
                object[] args = new object [1];
                args[0] = attribute.Number;
                PropertyInfo[] properties = new PropertyInfo [2];
                properties[0] = attrtype.GetProperty("ActivationType");
                properties[1] = attrtype.GetProperty("Repeatable");
                object[] values = new object [2];
                values[0] = attribute.ActivationType;
                values[1] = attribute.Repeatable;
                CustomAttributeBuilder builder = new CustomAttributeBuilder(ctor,args,properties,values);
                method.SetCustomAttribute(builder);
            }
        }

        public override void Compile(DefinitionContext c)
        {
            if (method == null)
                throw new InvalidOperationException();
            CodeContext c2 = new CodeContext(c,method);
            // Fixed local is used for some expressions
            c2.IL.DeclareLocal(typeof(Fixed));
            c2.ParameterTypes.Add(typeof(ScriptLinedefSpecialEnvironment));
            statement.Compile(c2);
            c2.IL.Emit(OpCodes.Newobj,typeof(ApplicationException).GetConstructor(Type.EmptyTypes));
            c2.IL.ThrowException(typeof(ApplicationException));
        }
    }
}
