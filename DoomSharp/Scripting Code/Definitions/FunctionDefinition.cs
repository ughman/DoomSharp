using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class FunctionDefinition : Definition
    {
        private string name;
        private string returntype;
        private string[] parametertypes;
        private string[] parameternames;
        private Statement statement;
        private MethodBuilder method;
        private Type realreturntype;
        private Type[] realparametertypes;

        public FunctionDefinition(string name,string returntype,string[] parametertypes,string[] parameternames,Statement statement)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            if (returntype == null)
                throw new ArgumentNullException("returntype");
            if (parametertypes == null)
                throw new ArgumentNullException("parametertypes");
            if (parameternames == null)
                throw new ArgumentNullException("parameternames");
            if (statement == null)
                throw new ArgumentNullException("statement");
            if (parametertypes.Length != parameternames.Length)
                throw new ArgumentException();
            this.name = name;
            this.returntype = returntype;
            this.parametertypes = parametertypes;
            this.parameternames = parameternames;
            this.statement = statement;
            this.method = null;
            this.realreturntype = null;
            this.realparametertypes = null;
        }

        public override void DefineMembers(DefinitionContext c)
        {
            if (method != null)
                throw new InvalidOperationException();
            if (!c.Types.TryGetValue(returntype,out realreturntype))
            {
                throw new ApplicationException();
            }
            realparametertypes = new Type [parametertypes.Length];
            for (int i = 0;i < parametertypes.Length;i++)
            {
                if (!c.Types.TryGetValue(parametertypes[i],out realparametertypes[i]))
                {
                    throw new ApplicationException();
                }
            }
            method = c.Module.DefineGlobalMethod(name,MethodAttributes.Static | MethodAttributes.Public,realreturntype,realparametertypes);
            for (int i = 0;i < parameternames.Length;i++)
            {
                method.DefineParameter(i + 1,ParameterAttributes.None,parameternames[i]);
            }
            c.DefineMethod(name,method);
        }

        public override void Compile(DefinitionContext c)
        {
            if (method == null)
                throw new InvalidOperationException();
            CodeContext c2 = new CodeContext(c,method);
            // Fixed local is used for some expressions
            c2.IL.DeclareLocal(typeof(Fixed));
            for (int i = 0;i < parametertypes.Length;i++)
            {
                c2.ParameterTypes.Add(realparametertypes[i]);
                c2.Parameters.Add(parameternames[i],i);
            }
            statement.Compile(c2);
            if (realreturntype == typeof(void))
            {
                c2.IL.Emit(OpCodes.Ret);
            }
            else
            {
                c2.IL.Emit(OpCodes.Newobj,typeof(ApplicationException).GetConstructor(Type.EmptyTypes));
                c2.IL.ThrowException(typeof(ApplicationException));
            }
        }
    }
}
