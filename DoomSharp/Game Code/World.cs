using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class World
    {
        private List<Thinker> thinkers;
        private List<Vertex> vertices;
        private List<Sector> sectors;
        private List<Sidedef> sidedefs;
        private List<Linedef> linedefs;
        private List<Thing> things;
        private Blockmap blockmap;

        public World()
        {
            this.thinkers = new List<Thinker>();
            this.vertices = new List<Vertex>();
            this.sectors = new List<Sector>();
            this.sidedefs = new List<Sidedef>();
            this.linedefs = new List<Linedef>();
            this.things = new List<Thing>();
            this.blockmap = null;
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

        public Blockmap Blockmap
        {
            get
            {
                if (blockmap == null)
                    throw new InvalidOperationException();
                return blockmap;
            }
            set
            {
                if (blockmap != null)
                    throw new InvalidOperationException();
                if (value.World != this)
                    throw new ArgumentException("Blockmap is from another world.");
                blockmap = value;
            }
        }

        public void AddThinker(Thinker thinker)
        {
            if (thinker == null)
                throw new ArgumentNullException("thinker");
            if (thinker.World != this)
                throw new ArgumentException("Thinker is from another world.");
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
