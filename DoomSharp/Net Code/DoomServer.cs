using System;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class DoomServer
    {
        private DoomSocket socket;
        private List<INetNode> nodes;

        public DoomServer(short port)
        {
            this.socket = new DoomSocket(port);
            socket.NodeAccepted += HandleNodeAccepted;
        }

        public void Run(int clients)
        {
            if (clients <= 0)
                throw new ArgumentOutOfRangeException("clients");
            nodes = new List<INetNode>();
            socket.AcceptNewNodes = true;
            while (nodes.Count < clients)
            {
                socket.Block();
                socket.Update();
            }
            socket.AcceptNewNodes = false;
            foreach (INetNode node in nodes)
            {
                node.PacketReceived -= HandleJoinPacket;
                node.PacketReceived += HandleGamePacket;
            }
            while (true)
            {
                socket.Block();
                socket.Update();
            }
        }
        
        private void HandleNodeAccepted(object sender,NetNodeEventArgs e)
        {
            nodes.Add(e.Node);
            e.Node.PacketReceived += HandleJoinPacket;
        }

        private void HandleJoinPacket(object sender,PacketEventArgs e)
        {
            INetNode node = (INetNode)sender;
            if (e.Type == PacketType.Connect)
            {
                node.SendPacket(PacketType.Waiting,new byte [0]);
            }
        }

        private void HandleGamePacket(object sender,PacketEventArgs e)
        {
            INetNode node = (INetNode)sender;
            if (e.Type == PacketType.Connect)
            {
                if (e.Data.Length != 0)
                    return;
                byte[] data = new byte [8];
                BitConv.ToInt32(data,0,nodes.IndexOf(node));
                BitConv.ToInt32(data,4,nodes.Count);
                node.SendPacket(PacketType.Accepted,data);
            }
            else if (e.Type == PacketType.DoomData)
            {
                if (e.Data.Length < 4)
                    return;
                int nodeid = BitConv.FromInt32(e.Data,0);
                if (nodeid < 0 || nodeid >= nodes.Count)
                    return;
                byte[] data = new byte [e.Data.Length];
                BitConv.ToInt32(data,0,nodes.IndexOf(node));
                Array.Copy(e.Data,4,data,4,e.Data.Length - 4);
                nodes[nodeid].SendPacket(PacketType.DoomData,data);
            }
        }
    }
}
