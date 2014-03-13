using System;
using System.Collections.Generic;

namespace DoomSharp
{
    [Scriptable]
    public sealed class World
    {
        private List<Thinker> thinkers;
        private List<Vertex> vertices;
        private List<Sector> sectors;
        private List<Sidedef> sidedefs;
        private List<Linedef> linedefs;
        private List<Thing> things;

        public World()
        {
            this.thinkers = new List<Thinker>();
            this.vertices = new List<Vertex>();
            this.sectors = new List<Sector>();
            this.sidedefs = new List<Sidedef>();
            this.linedefs = new List<Linedef>();
            this.things = new List<Thing>();
        }

        public IEnumerable<Thinker> Thinkers
        {
            get { return thinkers; }
        }

        public IList<Vertex> Vertices
        {
            get { return vertices; }
        }

        public IList<Sector> Sectors
        {
            get { return sectors; }
        }

        public IList<Sidedef> Sidedefs
        {
            get { return sidedefs; }
        }

        public IList<Linedef> Linedefs
        {
            get { return linedefs; }
        }

        public IList<Thing> Things
        {
            get { return things; }
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
