using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class Block
    {
        private Blockmap blockmap;
        private Actor firstactor;
        private List<Linedef> linedefs;

        public Block(Blockmap blockmap)
        {
            if (blockmap == null)
                throw new ArgumentNullException("blockmap");
            this.blockmap = blockmap;
            this.firstactor = null;
            this.linedefs = new List<Linedef>();
        }

        public Blockmap Blockmap
        {
            get { return blockmap; }
        }

        internal Actor FirstActor
        {
            get { return firstactor; }
            set { firstactor = value; }
        }

        public IEnumerable<Actor> Actors
        {
            get
            {
                for (Actor actor = firstactor;actor != null;actor = actor.NextInBlock)
                {
                    yield return actor;
                }
            }
        }

        public IEnumerable<Linedef> Linedefs
        {
            get { return linedefs; }
        }

        public void AddLinedef(Linedef linedef)
        {
            if (linedef == null)
                throw new ArgumentNullException("linedef");
            if (linedef.World != blockmap.World)
                throw new ArgumentException("Linedef is from another world.");
            if (linedefs.Contains(linedef))
            {
                Core.Console.LogWarning("A linedef has been added to a block it already exists in.");
            }
            linedefs.Add(linedef);
        }
    }
}
