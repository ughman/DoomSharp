using System;

namespace DoomSharp
{
    public class NetNodeEventArgs : EventArgs
    {
        private INetNode node;

        public INetNode Node
        {
            get { return node; }
            set { node = value; }
        }
    }
}
