using System;

namespace DoomSharp
{
    public class ScriptSpecialEnvironment : ScriptEnvironment
    {
        private Actor activator;

        public ScriptSpecialEnvironment(World world,Actor activator) : base(world)
        {
            // Activator can be null
            this.activator = activator;
        }

        public ScriptSpecialEnvironment(ScriptSpecialEnvironment environment) : base(environment)
        {
            if (environment == null)
                throw new ArgumentNullException("environment");
            this.activator = environment.activator;
        }

        public Actor Activator
        {
            get { return activator; }
        }
    }
}
