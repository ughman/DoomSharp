using System;

namespace DoomSharp
{
    public class ScriptLinedefSpecialEnvironment : ScriptSpecialEnvironment
    {
        private Linedef linedef;
        private bool isbackside;

        public ScriptLinedefSpecialEnvironment(World world,Actor activator,Linedef linedef,bool isbackside) : base(world,activator)
        {
            if (linedef == null)
                throw new ArgumentNullException("linedef");
            this.linedef = linedef;
            this.isbackside = isbackside;
        }

        public ScriptLinedefSpecialEnvironment(ScriptLinedefSpecialEnvironment environment) : base(environment)
        {
            if (environment == null)
                throw new ArgumentNullException("environment");
            this.linedef = environment.linedef;
            this.isbackside = environment.isbackside;
        }

        public Linedef Linedef
        {
            get { return linedef; }
        }

        public bool IsBackSide
        {
            get { return isbackside; }
        }
    }
}
