using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

namespace DoomSharp
{
    public sealed class DoomSocket : INetSocket
    {
        private const int Magic = 0x12121213;
        private const int HeaderSize = 5;

        private Socket socket;
        private Dictionary<EndPoint,Node> nodes;
        private bool acceptnewnodes;

        public event EventHandler<NetNodeEventArgs> NodeAccepted;

        public DoomSocket()
        {
            this.socket = new Socket(AddressFamily.InterNetwork,SocketType.Dgram,ProtocolType.Udp);
            this.nodes = new Dictionary<EndPoint,Node>();
            this.acceptnewnodes = false;
        }

        public DoomSocket(short port) : this()
        {
            socket.Bind(new IPEndPoint(IPAddress.Any,port));
        }

        public bool AcceptNewNodes
        {
            get { return acceptnewnodes; }
            set { acceptnewnodes = value; }
        }

        public INetNode Connect(EndPoint endpoint)
        {
            if (endpoint == null)
                throw new ArgumentNullException("endpoint");
            if (nodes.ContainsKey(endpoint))
            {
                return nodes[endpoint];
            }
            else
            {
                Node node = new Node(this,endpoint);
                nodes.Add(endpoint,node);
                return node;
            }
        }

        public void Update()
        {
            byte[] buffer = new byte [1024];
            while (socket.Available > 0)
            {
                try
                {
                    EndPoint endpoint = new IPEndPoint(IPAddress.Any,0);
                    int length = socket.ReceiveFrom(buffer,ref endpoint);
                    if (length > buffer.Length)
                        continue;
                    if (length < HeaderSize)
                        continue;
                    int magic = BitConv.FromInt32(buffer,0);
                    PacketType type = (PacketType)buffer[4];
                    if (magic != Magic)
                        continue;
                    byte[] data = new byte [length - HeaderSize];
                    Array.Copy(buffer,HeaderSize,data,0,data.Length);
                    ReceivePacket(endpoint,type,data);
                }
                catch (SocketException)
                {
                    // TODO :: Log exception
                }
            }
        }

        public void Block()
        {
            socket.Poll(-1,SelectMode.SelectRead);
        }

        public void Dispose()
        {
            socket.Close();
        }

        private void SendPacket(EndPoint endpoint,PacketType type,byte[] data)
        {
            byte[] buffer = new byte [HeaderSize + data.Length];
            BitConv.ToInt32(buffer,0,Magic);
            buffer[4] = (byte)type;
            data.CopyTo(buffer,HeaderSize);
            socket.SendTo(buffer,endpoint);
        }

        private void ReceivePacket(EndPoint endpoint,PacketType type,byte[] data)
        {
            if (nodes.ContainsKey(endpoint))
            {
                nodes[endpoint].ReceivePacket(type,data);
            }
            else if (acceptnewnodes)
            {
                Node node = new Node(this,endpoint);
                nodes.Add(endpoint,node);
                if (NodeAccepted != null)
                {
                    NetNodeEventArgs e = new NetNodeEventArgs();
                    e.Node = node;
                    NodeAccepted(this,e);
                }
                node.ReceivePacket(type,data);
            }
        }

        private sealed class Node : INetNode
        {
            private DoomSocket socket;
            private EndPoint endpoint;

            public event EventHandler<PacketEventArgs> PacketReceived;

            public Node(DoomSocket socket,EndPoint endpoint)
            {
                this.socket = socket;
                this.endpoint = endpoint;
            }

            public void SendPacket(PacketType type,byte[] data)
            {
                if (data == null)
                    throw new ArgumentNullException("data");
                socket.SendPacket(endpoint,type,data);
            }

            public void ReceivePacket(PacketType type,byte[] data)
            {
                if (PacketReceived != null)
                {
                    PacketEventArgs e = new PacketEventArgs();
                    e.Type = type;
                    e.Data = data;
                    PacketReceived(this,e);
                }
            }
        }
    }
}
