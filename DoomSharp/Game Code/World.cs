using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class World
    {
        private List<Thinker> thinkers;
        private List<Vertex> vertices;

        public World()
        {
            this.thinkers = new List<Thinker>();
            this.vertices = new List<Vertex>();
        }

        public IEnumerable<Thinker> Thinkers
        {
            get { return thinkers; }
        }

        public IList<Vertex> Vertices
        {
            get { return vertices; }
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
