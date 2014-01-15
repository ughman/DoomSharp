using namespace System;
using namespace System::Net;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace DoomSharp;

extern "C"
{
#include "i_net.h"
#include "d_net.h"
#include "doomstat.h"
#include "m_argv.h"
#include "i_system.h"
}

#include <vcclr.h>
#include <stdlib.h>

gcroot<INetSocket^> socket;
gcroot<INetNode^> server;
gcroot<List<int>^> doomnodes;
gcroot<Queue<array<unsigned char>^>^> doompackets;

void HandleJoinPacket(Object^ sender,PacketEventArgs^ e)
{
	if (e->Type == PacketType::Waiting)
	{
		Console::WriteLine("(waiting for game to start)");
	}
	else if (e->Type == PacketType::Accepted)
	{
		if (e->Data->Length != 8)
			return;
		int mydoomnode = BitConv::FromInt32(e->Data,0);
		int doomnodecount = BitConv::FromInt32(e->Data,4);
		if (doomnodecount < 1)
			return;
		if (mydoomnode < 0)
			return;
		if (mydoomnode >= doomnodecount)
			return;
		doomnodes = gcnew List<int>(doomnodecount);
		for (int i = 0;i < doomnodecount;i++)
		{
			doomnodes->Add(i);
		}
		doomnodes->RemoveAt(mydoomnode);
		doomnodes->Insert(0,mydoomnode);
		server->PacketReceived -= gcnew EventHandler<PacketEventArgs^>(HandleJoinPacket);
	}
}

void HandleGamePacket(Object^ sender,PacketEventArgs^ e)
{
	if (e->Type == PacketType::DoomData)
	{
		if (e->Data->Length < 4)
			return;
		doompackets->Enqueue(e->Data);
	}
}

extern "C" void I_InitNetwork()
{
	doomcom = new doomcom_t;
	memset(doomcom,0,sizeof(doomcom_t));
	doomcom->ticdup = 1;
	doomcom->id = DOOMCOM_ID;
	if (int p = M_CheckParm("-connect"))
	{
		IPAddress^ address = IPAddress::Parse(gcnew String(myargv[p + 1]));
		long port = strtol(myargv[p + 2],NULL,10);
		socket = gcnew DoomSocket();
		server = socket->Connect(gcnew IPEndPoint(address,port));
		server->PacketReceived += gcnew EventHandler<PacketEventArgs^>(HandleJoinPacket);
		while (!doomnodes)
		{
			Console::WriteLine("Connecting to server...");
			array<unsigned char>^ data = gcnew array<unsigned char>(0);
			server->SendPacket(PacketType::Connect,data);
			Thread::Sleep(1000);
			socket->Update();
		}
		netgame = true;
		if (doomnodes->Count <= MAXPLAYERS)
		{
			doomcom->numplayers = doomcom->numnodes = doomnodes->Count;
		}
		else
		{
			doomcom->numplayers = MAXPLAYERS;
			doomcom->numnodes = doomnodes->Count;
		}
		if (doomnodes->default[0] < MAXPLAYERS)
		{
			doomcom->consoleplayer = doomnodes->default[0];
		}
		else
		{
			doomcom->consoleplayer = 0;
			doomcom->drone = true;
		}
		doompackets = gcnew Queue<array<unsigned char>^>();
		server->PacketReceived += gcnew EventHandler<PacketEventArgs^>(HandleGamePacket);
	}
	else
	{
		netgame = false;
		doomcom->numplayers = doomcom->numnodes = 1;
	}
}

extern "C" void I_NetCmd()
{
	if (doomcom->command == CMD_GET)
	{
		socket->Update();
		if (doompackets->Count > 0)
		{
			array<unsigned char>^ data = doompackets->Dequeue();
			int sourcenode = BitConv::FromInt32(data,0);
			if (sourcenode < 0 || sourcenode >= doomnodes->Count)
				I_Error("I_NetCmd: Received packet from invalid node id");
			doomcom->remotenode = doomnodes->IndexOf(sourcenode);
			doomcom->datalength = data->Length - 4;
			if (doomcom->datalength > sizeof(doomcom->data))
				I_Error("I_NetCmd: Received packet with invalid length");
			Marshal::Copy(data,4,(IntPtr)&doomcom->data,doomcom->datalength);
		}
		else
		{
			doomcom->remotenode = -1;
		}
	}
	else if (doomcom->command == CMD_SEND)
	{
		array<unsigned char>^ data = gcnew array<unsigned char>(4 + doomcom->datalength);
		BitConv::ToInt32(data,0,doomnodes->default[doomcom->remotenode]);
		Marshal::Copy((IntPtr)&doomcom->data,data,4,doomcom->datalength);
		server->SendPacket(PacketType::DoomData,data);
	}
	else
	{
		I_Error("I_NetCmd: Unknown command");
	}
}
