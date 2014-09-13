using System;

namespace DoomSharp
{
    public class ScriptEnvironment
    {
        private World world;

        public ScriptEnvironment(World world)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            this.world = world;
        }

        public ScriptEnvironment(ScriptEnvironment environment)
        {
            if (environment == null)
                throw new ArgumentNullException("environment");
            this.world = environment.world;
        }

        public World World
        {
            get { return world; }
        }
    }
}
