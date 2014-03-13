using System;
using System.Reflection;
using System.Collections.Generic;

namespace DoomSharp
{
    public static class Registrar
    {
        private static List<Type> types;
        private static List<MethodInfo> methods;
        private static List<RegistrarTypeHandler> typehandlers;
        private static List<RegistrarMethodHandler> methodhandlers;

        static Registrar()
        {
            types = new List<Type>();
            methods = new List<MethodInfo>();
            typehandlers = new List<RegistrarTypeHandler>();
            methodhandlers = new List<RegistrarMethodHandler>();
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
            foreach (RegistrarTypeHandler handler in typehandlers)
            {
                handler(type);
            }
        }

        public static void RegisterMethod(MethodInfo method)
        {
            if (method == null)
                throw new ArgumentNullException("method");
            methods.Add(method);
            foreach (RegistrarMethodHandler handler in methodhandlers)
            {
                handler(method);
            }
            if (method.IsDefined(typeof(RegistrarTypeHandlerAttribute),false))
            {
                RegistrarTypeHandler handler = (RegistrarTypeHandler)Delegate.CreateDelegate(typeof(RegistrarTypeHandler),method);
                typehandlers.Add(handler);
                foreach (Type type in types)
                {
                    handler(type);
                }
            }
            if (method.IsDefined(typeof(RegistrarMethodHandlerAttribute),false))
            {
                RegistrarMethodHandler handler = (RegistrarMethodHandler)Delegate.CreateDelegate(typeof(RegistrarMethodHandler),method);
                methodhandlers.Add(handler);
                foreach (MethodInfo method2 in methods)
                {
                    handler(method2);
                }
            }
        }
    }
}
