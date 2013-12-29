using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class MultiArchive : IArchive
    {
        private List<IArchive> archives;

        public MultiArchive()
        {
            this.archives = new List<IArchive>();
        }

        public int LumpCount
        {
            get
            {
                int result = 0;
                foreach (IArchive archive in archives)
                {
                    result += archive.LumpCount;
                }
                return result;
            }
        }

        public ILump this[int i]
        {
            get
            {
                if (i < 0)
                    throw new IndexOutOfRangeException();
                foreach (IArchive archive in archives)
                {
                    if (i >= archive.LumpCount)
                    {
                        i -= archive.LumpCount;
                    }
                    else
                    {
                        return archive[i];
                    }
                }
                throw new IndexOutOfRangeException();
            }
        }

        public int Find(string name)
        {
            if (name == null)
                throw new ArgumentNullException("name");
            name = name.ToUpper();
            int offset = 0;
            foreach (IArchive archive in archives)
            {
                for (int i = 0;i < archive.LumpCount;i++)
                {
                    if (archive[i].Name == name)
                    {
                        return offset + i;
                    }
                }
                offset += archive.LumpCount;
            }
            throw new LumpNotFoundException(name);
        }

        public void AddArchive(IArchive archive)
        {
            if (archive == null)
                throw new ArgumentNullException("archive");
            archives.Add(archive);
        }
    }
}
