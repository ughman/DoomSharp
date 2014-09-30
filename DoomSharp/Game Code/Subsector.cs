using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public abstract class Subsector
    {
        private World world;
        private Sector sector;
        private List<Seg> segs;

        public Subsector(World world,Sector sector)
        {
            if (world == null)
                throw new ArgumentNullException("world");
            if (sector == null)
                throw new ArgumentNullException("sector");
            if (sector.World != world)
                throw new ArgumentException("Sector is from another world.");
            this.world = world;
            this.sector = sector;
            this.segs = new List<Seg>();
        }

        public World World
        {
            get { return world; }
        }

        public Sector Sector
        {
            get { return sector; }
        }

        public IEnumerable<Seg> Segs
        {
            get { return segs; }
        }

        public void AddSeg(Seg seg)
        {
            if (seg == null)
                throw new ArgumentNullException("seg");
            if (seg.World != world)
                throw new ArgumentException("Seg is from another world.");
            if (seg.Front == null || seg.Front.Sector != sector)
                Core.Console.LogWarning("A seg has been added to a subsector for another sector.");
            if (segs.Contains(seg))
                Core.Console.LogWarning("A seg has been added to a subsector it already exists in.");
            segs.Add(seg);
        }
    }
}
