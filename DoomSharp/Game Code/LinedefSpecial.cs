using System;
using System.Reflection;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class LinedefSpecial
    {
        private static Dictionary<int,LinedefSpecial> specials;

        static LinedefSpecial()
        {
            specials = new Dictionary<int,LinedefSpecial>();
        }

        [RegistrarMethodHandler]
        private static void RegisterMethod(MethodInfo method)
        {
            foreach (LinedefSpecialAttribute attribute in method.GetCustomAttributes(typeof(LinedefSpecialAttribute),false))
            {
                LinedefSpecialHandler handler = (LinedefSpecialHandler)Delegate.CreateDelegate(typeof(LinedefSpecialHandler),method);
                specials[attribute.Number] = new LinedefSpecial(handler,attribute.ActivationType,attribute.Repeatable);
            }
        }

        public static LinedefSpecial GetSpecial(int number)
        {
            LinedefSpecial result;
            if (specials.TryGetValue(number,out result))
                return result;
            return null;
        }

        private LinedefSpecialHandler handler;
        private LinedefActivationType activationtype;
        private bool repeatable;

        private LinedefSpecial(LinedefSpecialHandler handler,LinedefActivationType activationtype,bool repeatable)
        {
            if (handler == null)
                throw new ArgumentNullException("handler");
            this.handler = handler;
            this.activationtype = activationtype;
            this.repeatable = repeatable;
        }

        public LinedefActivationType ActivationType
        {
            get { return activationtype; }
        }

        public bool Repeatable
        {
            get { return repeatable; }
        }

        public bool Activate(Actor activator,Linedef linedef,bool isbackside)
        {
            // Activator can be null
            if (linedef == null)
                throw new ArgumentNullException("linedef");
            return handler(new ScriptLinedefSpecialEnvironment(activator.World,activator,linedef,isbackside));
        }

        public delegate bool LinedefSpecialHandler(ScriptLinedefSpecialEnvironment environment);
    }
}
