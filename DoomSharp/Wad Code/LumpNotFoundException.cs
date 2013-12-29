using System;
using System.Runtime.Serialization;

namespace DoomSharp
{
    public class LumpNotFoundException : Exception
    {
        public LumpNotFoundException(string lumpname) : base(string.Format("The lump '{0}' could not be found.",lumpname))
        {
        }

        protected LumpNotFoundException(SerializationInfo info,StreamingContext context) : base(info,context)
        {
        }
    }
}
