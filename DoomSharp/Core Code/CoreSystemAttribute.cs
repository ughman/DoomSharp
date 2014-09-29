using System;

namespace DoomSharp
{
    public sealed class CoreSystemAttribute : Attribute
    {
        private string type;
        private string name;
        private string nicename;

        public CoreSystemAttribute(string type,string name,string nicename)
        {
            if (type == null)
                throw new ArgumentNullException("type");
            if (name == null)
                throw new ArgumentNullException("name");
            if (nicename == null)
                throw new ArgumentNullException("nicename");
            this.type = type;
            this.name = name;
            this.nicename = nicename;
        }

        public string Type
        {
            get { return type; }
        }

        public string Name
        {
            get { return name; }
        }

        public string NiceName
        {
            get { return nicename; }
        }
    }
}
