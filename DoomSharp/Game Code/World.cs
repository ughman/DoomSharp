using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class World
    {
        private Chain<Thinker> thinkers;
        private List<Vertex> vertices;
        private List<Sector> sectors;
        private List<Sidedef> sidedefs;
        private List<Linedef> linedefs;
        private List<Thing> things;
        private Blockmap blockmap;

        public World()
        {
            this.thinkers = new Chain<Thinker>();
            this.vertices = new List<Vertex>();
            this.sectors = new List<Sector>();
            this.sidedefs = new List<Sidedef>();
            this.linedefs = new List<Linedef>();
            this.things = new List<Thing>();
            this.blockmap = null;
        }

        [Scriptable]
        public IEnumerable<Thinker> Thinkers
        {
            get { return thinkers; }
        }

        [Scriptable]
        public IList<Vertex> Vertices
        {
            get { return vertices; }
        }

        [Scriptable]
        public IList<Sector> Sectors
        {
            get { return sectors; }
        }

        [Scriptable]
        public IList<Sidedef> Sidedefs
        {
            get { return sidedefs; }
        }

        [Scriptable]
        public IList<Linedef> Linedefs
        {
            get { return linedefs; }
        }

        [Scriptable]
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

        internal void AddThinker(Thinker thinker)
        {
            // Called from thinker.Start
            // No need to do any additional checks
            thinkers.Add(thinker);
        }

        internal void RemoveThinker(Thinker thinker)
        {
            // Called from thinker.Stop
            // No need to do any additional checks
            thinkers.Remove(thinker);
        }

        public void Tick()
        {
            foreach (Thinker thinker in thinkers)
            {
                if (thinker.Tick())
                    thinker.Stop();
            }
        }
    }
}
