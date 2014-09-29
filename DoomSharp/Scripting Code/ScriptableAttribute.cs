using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Field | AttributeTargets.Property)]
    public sealed class ScriptableAttribute : Attribute
    {
        private string name;

        public ScriptableAttribute()
        {
            this.name = null;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }
}
