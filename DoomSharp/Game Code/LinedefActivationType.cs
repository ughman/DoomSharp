using System;

namespace DoomSharp
{
    [Flags]
    public enum LinedefActivationType
    {
        None = 0,
        Automatic = 1,
        Use = 2,
        MonsterUse = 4,
        Cross = 8,
        MonsterCross = 16,
        Shoot = 32,
        MonsterShoot = 64
    }
}
