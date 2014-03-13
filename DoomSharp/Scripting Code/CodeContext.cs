using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class CodeContext : DefinitionContext
    {
        private MethodBuilder method;
        private ILGenerator il;
        private Dictionary<string,LocalBuilder> locals;
        private Dictionary<string,int> parameters;
        private List<Type> parametertypes;

        public CodeContext(DefinitionContext next,MethodBuilder method) : base(next)
        {
            if (method == null)
                throw new ArgumentNullException("method");
            this.method = method;
            this.il = method.GetILGenerator();
            this.locals = new Dictionary<string,LocalBuilder>();
            this.parameters = new Dictionary<string,int>();
            this.parametertypes = new List<Type>();
        }

        public CodeContext(CodeContext next) : base(next)
        {
            if (next == null)
                throw new ArgumentNullException("next");
            this.method = next.method;
            this.il = next.il;
            this.locals = new Dictionary<string,LocalBuilder>(next.locals);
            this.parameters = next.parameters;
            this.parametertypes = next.parametertypes;
        }

        public MethodBuilder Method
        {
            get { return method; }
        }

        public ILGenerator IL
        {
            get { return il; }
        }

        public IDictionary<string,LocalBuilder> Locals
        {
            get { return locals; }
        }

        public IDictionary<string,int> Parameters
        {
            get { return parameters; }
        }

        public IList<Type> ParameterTypes
        {
            get { return parametertypes; }
        }

        public void Convert(Type source,Type destination)
        {
            if (destination == null)
                throw new ArgumentNullException("destination");
            // Source may be null if from NullExpression
            if (source == null && !destination.IsValueType)
            {
                // null -> reference type is compatible
                return;
            }
            else if (destination.IsAssignableFrom(source))
            {
                if (source.IsValueType && !destination.IsValueType)
                {
                    // Value type must be boxed
                    il.Emit(OpCodes.Box,source);
                }
            }
            else if (source == typeof(int) && destination == typeof(Fixed))
            {
                // int -> Fixed conversion
                il.Emit(OpCodes.Call,typeof(Fixed).GetMethod("FromInt"));
            }
            else
            {
                throw new ApplicationException();
            }
        }
    }
}
