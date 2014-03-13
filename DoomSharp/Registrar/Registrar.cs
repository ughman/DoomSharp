using System;
using System.Reflection;
using System.Collections.Generic;

namespace DoomSharp
{
    public static class Registrar
    {
        private static List<Type> types;
        private static List<MethodInfo> methods;

        static Registrar()
        {
            types = new List<Type>();
            methods = new List<MethodInfo>();
        }

        public static void RegisterAssembly(Assembly assembly)
        {
            if (assembly == null)
                throw new ArgumentNullException("assembly");
            foreach (Module module in assembly.GetModules())
            {
                RegisterModule(module);
            }
        }

        public static void RegisterModule(Module module)
        {
            if (module == null)
                throw new ArgumentNullException("module");
            foreach (Type type in module.GetTypes())
            {
                RegisterType(type);
            }
            foreach (MethodInfo method in module.GetMethods())
            {
                RegisterMethod(method);
            }
        }

        public static void RegisterType(Type type)
        {
            if (type == null)
                throw new ArgumentNullException("type");
            foreach (MethodInfo method in type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Static))
            {
                RegisterMethod(method);
            }
            types.Add(type);
            foreach (MethodInfo method in methods)
            {
                method.Invoke(null,new object[] {type});
            }
        }

        public static void RegisterMethod(MethodInfo method)
        {
            if (method == null)
                throw new ArgumentNullException("method");
            if (method.IsDefined(typeof(RegistrarTypeHandlerAttribute),false))
            {
                methods.Add(method);
                foreach (Type type in types)
                {
                    method.Invoke(null,new object[] {type});
                }
            }
        }
    }
}
