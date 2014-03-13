using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public class DefinitionContext
    {
        private static Dictionary<string,Type> globaltypes;
        private static Dictionary<string,MethodInfo> globalmethods;

        static DefinitionContext()
        {
            globaltypes = new Dictionary<string,Type>();
            globalmethods = new Dictionary<string,MethodInfo>();
            globaltypes.Add("void",typeof(void));
            globaltypes.Add("int",typeof(int));
            globaltypes.Add("fixed",typeof(Fixed));
            globaltypes.Add("string",typeof(string));
            globaltypes.Add("object",typeof(object));
            globaltypes.Add("Actor",typeof(Actor));
        }

        private ModuleBuilder module;
        private Dictionary<string,Type> types;
        private Dictionary<string,MethodInfo> methods;

        public DefinitionContext(ModuleBuilder module)
        {
            if (module == null)
                throw new ArgumentNullException("module");
            this.module = module;
            this.types = new Dictionary<string,Type>(globaltypes);
            this.methods = new Dictionary<string,MethodInfo>(globalmethods);
        }

        protected DefinitionContext(DefinitionContext next)
        {
            if (next == null)
                throw new ArgumentNullException("next");
            this.module = next.module;
            this.types = next.types;
            this.methods = next.methods;
        }

        public ModuleBuilder Module
        {
            get { return module; }
        }

        public void DefineType(string name,Type type)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            if (type == null)
                throw new ArgumentNullException("type");
            types[name] = type;
        }

        public void DefineMethod(string name,MethodInfo method)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            if (method == null)
                throw new ArgumentNullException("method");
            methods[name] = method;
        }

        public IDictionary<string,Type> Types
        {
            get { return types; }
        }

        public IDictionary<string,MethodInfo> Methods
        {
            get { return methods; }
        }
    }
}
