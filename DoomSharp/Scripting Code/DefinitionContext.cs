using System;
using System.Reflection;
using System.Reflection.Emit;
using System.Collections.Generic;

namespace DoomSharp
{
    public class DefinitionContext
    {
        private static AssemblyBuilder assembly;
        private static Dictionary<string,Type> globaltypes;
        private static Dictionary<string,MethodInfo> globalmethods;

        static DefinitionContext()
        {
            AssemblyName assemblyname = new AssemblyName("DoomSharp.Dynamic");
            assembly = AppDomain.CurrentDomain.DefineDynamicAssembly(assemblyname,AssemblyBuilderAccess.Run);
            globaltypes = new Dictionary<string,Type>();
            globalmethods = new Dictionary<string,MethodInfo>();
            globaltypes.Add("void",typeof(void));
            globaltypes.Add("int",typeof(int));
            globaltypes.Add("fixed",typeof(Fixed));
            globaltypes.Add("string",typeof(string));
            globaltypes.Add("object",typeof(object));
        }

        [RegistrarTypeHandler]
        private static void RegisterType(Type type)
        {
            if (type.IsDefined(typeof(ScriptableAttribute),true))
            {
                globaltypes[type.Name] = type;
            }
        }

        [RegistrarMethodHandler]
        private static void RegisterMethod(MethodInfo method)
        {
            if (method.IsDefined(typeof(ScriptableAttribute),false))
            {
                globalmethods[method.Name] = method;
            }
        }

        private ModuleBuilder module;
        private TypeBuilder globaltype;
        private Dictionary<string,Type> types;
        private Dictionary<string,MethodInfo> methods;

        public DefinitionContext(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            this.module = assembly.DefineDynamicModule(name);
            this.globaltype = module.DefineType("Global",TypeAttributes.Public);
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
            get
            {
                if (module == null)
                    throw new InvalidOperationException();
                return module;
            }
        }

        public TypeBuilder GlobalType
        {
            get
            {
                if (module == null)
                    throw new InvalidOperationException();
                return globaltype;
            }
        }

        public void DefineType(string name,Type type)
        {
            if (module == null)
                throw new InvalidOperationException();
            if (name == null)
                throw new ArgumentNullException("name");
            if (type == null)
                throw new ArgumentNullException("type");
            types[name] = type;
        }

        public void DefineMethod(string name,MethodInfo method)
        {
            if (module == null)
                throw new InvalidOperationException();
            if (name == null)
                throw new ArgumentNullException("name");
            if (method == null)
                throw new ArgumentNullException("method");
            methods[name] = method;
        }

        public IDictionary<string,Type> Types
        {
            get
            {
                if (module == null)
                    throw new InvalidOperationException();
                return types;
            }
        }

        public IDictionary<string,MethodInfo> Methods
        {
            get
            {
                if (module == null)
                    throw new InvalidOperationException();
                return methods;
            }
        }

        public void Complete()
        {
            if (module == null)
                throw new InvalidOperationException();
            globaltype.CreateType();
            foreach (Type type in types.Values)
            {
                if (type is TypeBuilder)
                {
                    ((TypeBuilder)type).CreateType();
                }
            }
            module.CreateGlobalFunctions();
            Registrar.RegisterModule(module);
            module = null;
        }
    }
}
