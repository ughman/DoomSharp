using System;

namespace DoomSharp
{
    public interface INetNode
    {
        event EventHandler<PacketEventArgs> PacketReceived;

        void SendPacket(PacketType type,byte[] data);
    }
}
