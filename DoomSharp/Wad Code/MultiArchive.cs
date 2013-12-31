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
            int offset = LumpCount;
            for (int i = archives.Count - 1;i >= 0;i--)
            {
                offset -= archives[i].LumpCount;
                for (int ii = 0;ii < archives[i].LumpCount;ii++)
                {
                    if (archives[i][ii].Name == name)
                    {
                        return offset + ii;
                    }
                }
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
