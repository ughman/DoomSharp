using System;

namespace DoomSharp
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Field | AttributeTargets.Property)]
    public sealed class ScriptableAttribute : Attribute
    {
        private ScriptAccessType accesstype;
        private string name;

        public ScriptableAttribute() : this(ScriptAccessType.Full)
        {
        }

        public ScriptableAttribute(ScriptAccessType accesstype)
        {
            this.accesstype = accesstype;
            this.name = null;
        }

        public ScriptAccessType AccessType
        {
            get { return accesstype; }
            set { accesstype = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    }
}
