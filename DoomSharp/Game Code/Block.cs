using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class Block
    {
        private Blockmap blockmap;
        private Chain<Actor> actors;
        private List<Linedef> linedefs;

        public Block(Blockmap blockmap)
        {
            if (blockmap == null)
                throw new ArgumentNullException("blockmap");
            this.blockmap = blockmap;
            this.actors = new Chain<Actor>();
            this.linedefs = new List<Linedef>();
        }

        public Blockmap Blockmap
        {
            get { return blockmap; }
        }

        public IEnumerable<Actor> Actors
        {
            get { return actors; }
        }

        public IEnumerable<Linedef> Linedefs
        {
            get { return linedefs; }
        }

        public void AddActor(Actor actor)
        {
            if (actor == null)
                throw new ArgumentNullException("actor");
            if (actor.World != blockmap.World)
                throw new ArgumentException("Actor is from another world.");
            if (actors.Contains(actor))
            {
                Core.Console.LogWarning("An actor ({0}) has been added to a block it already exists in.",actor);
            }
            actors.AddFront(actor);
        }

        public void RemoveActor(Actor actor)
        {
            if (actor == null)
                throw new ArgumentNullException("actor");
            if (!actors.Remove(actor))
            {
                Core.Console.LogWarning("An actor ({0}) has been removed from a block it doesn't exist in.",actor);
            }
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
