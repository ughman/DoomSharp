using System;
using System.Reflection;
using System.Reflection.Emit;

namespace DoomSharp
{
    public sealed class MemberExpression : UnaryExpression
    {
        private string membername;

        public MemberExpression(Expression inner,string membername) : base(inner)
        {
            if (membername == null)
                throw new ArgumentNullException("membername");
            this.membername = membername;
        }

        public override Type Evaluate(CodeContext c)
        {
            Type type = Inner.Evaluate(c);
            MemberInfo member = GetMember(type);
            if (member.MemberType == MemberTypes.Field)
            {
                FieldInfo field = (FieldInfo)member;
                c.IL.Emit(OpCodes.Ldfld,field);
                return field.FieldType;
            }
            else if (member.MemberType == MemberTypes.Property)
            {
                PropertyInfo property = (PropertyInfo)member;
                if (!property.CanRead)
                {
                    throw new ApplicationException();
                }
                c.IL.Emit(OpCodes.Callvirt,property.GetGetMethod());
                return property.PropertyType;
            }
            else
            {
                throw new ApplicationException();
            }
        }

        public override void Assign(CodeContext c,Expression source)
        {
            Type type = Inner.Evaluate(c);
            MemberInfo member = GetMember(type);
            if (member.MemberType == MemberTypes.Field)
            {
                FieldInfo field = (FieldInfo)member;
                if (field.IsInitOnly || field.IsLiteral)
                {
                    throw new ApplicationException();
                }
                Type sourcetype = source.Evaluate(c);
                c.Convert(sourcetype,field.FieldType);
                c.IL.Emit(OpCodes.Stfld,field);
            }
            else if (member.MemberType == MemberTypes.Property)
            {
                PropertyInfo property = (PropertyInfo)member;
                if (!property.CanWrite)
                {
                    throw new ApplicationException();
                }
                Type sourcetype = source.Evaluate(c);
                c.Convert(sourcetype,property.PropertyType);
                c.IL.Emit(OpCodes.Callvirt,property.GetSetMethod());
            }
            else
            {
                throw new ApplicationException();
            }
        }

        public override Type Invoke(CodeContext c,Expression[] arguments)
        {
            Type type = Inner.Evaluate(c);
            MemberInfo member = GetMember(type);
            if (member.MemberType == MemberTypes.Method)
            {
                MethodInfo method = (MethodInfo)member;
                ParameterInfo[] parameters = method.GetParameters();
                if (parameters.Length != arguments.Length)
                {
                    throw new ApplicationException();
                }
                for (int i = 0;i < arguments.Length;i++)
                {
                    Type argumenttype = arguments[i].Evaluate(c);
                    c.Convert(argumenttype,parameters[i].ParameterType);
                }
                c.IL.Emit(OpCodes.Callvirt,method);
                return method.ReturnType;
            }
            else
            {
                throw new ApplicationException();
            }
        }

        private MemberInfo GetMember(Type type)
        {
            foreach (MemberInfo member in type.GetMembers(BindingFlags.Public | BindingFlags.Instance))
            {
                if (member.Name != membername)
                    continue;
                // TODO :: ScriptableAttribute check
                return member;
            }
            throw new ApplicationException();
        }
    }
}
