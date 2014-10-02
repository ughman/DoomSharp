using System;

namespace DoomSharp
{
    [Flags]
    public enum ScriptAccessType
    {
        Get = 1,
        Set = 2,
        Invoke = 4,
        Full = 7
    }
}
