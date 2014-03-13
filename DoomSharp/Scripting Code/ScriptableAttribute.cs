using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Field | AttributeTargets.Property)]
    public sealed class ScriptableAttribute : Attribute
    {
    }
}
