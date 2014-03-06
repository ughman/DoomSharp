using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class World
    {
        private List<Thinker> thinkers;

        public World()
        {
            this.thinkers = new List<Thinker>();
        }

        public IEnumerable<Thinker> Thinkers
        {
            get { return thinkers; }
        }

        public void AddThinker(Thinker thinker)
        {
            if (thinker == null)
                throw new ArgumentNullException("thinker");
            thinkers.Add(thinker);
        }

        public void Tick()
        {
            for (int i = 0;i < thinkers.Count;i++)
            {
                if (thinkers[i].Tick())
                {
                    thinkers.RemoveAt(i--);
                }
            }
        }
    }
}
