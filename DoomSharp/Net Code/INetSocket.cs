using System;
using System.Net;

namespace DoomSharp
{
    public interface INetSocket : IDisposable
    {
        event EventHandler<NetNodeEventArgs> NodeAccepted;

        bool AcceptNewNodes
        {
            get;
            set;
        }

        INetNode Connect(EndPoint endpoint);
        void Update();
        void Block();
    }
}
