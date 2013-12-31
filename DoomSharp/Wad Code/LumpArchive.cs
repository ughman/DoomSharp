using System;
using System.IO;
using System.Text;

namespace DoomSharp
{
    public sealed class LumpArchive : IArchive
    {
        private ILump lump;

        public LumpArchive(ILump lump)
        {
            if (lump == null)
                throw new ArgumentNullException("lump");
            this.lump = lump;
        }

        public int LumpCount
        {
            get { return 1; }
        }

        public ILump this[int i]
        {
            get
            {
                if (i < 0 || i >= 1)
                    throw new IndexOutOfRangeException();
                return lump;
            }
        }

        public int Find(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            if (name.ToUpper() != lump.Name)
                throw new LumpNotFoundException(name);
            return 0;
        }
    }
}
