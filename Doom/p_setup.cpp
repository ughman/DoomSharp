#include "p_setup.hpp"

extern "C"
{
#include "i_system.h"
}

extern "C" void P_LoadVertexes(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 4;
	if (data->Length % 4)
		Core::Console->LogWarning("This map's VERTEXES lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		short x = BitConv::FromInt16(data,i * 4 + 0);
		short y = BitConv::FromInt16(data,i * 4 + 2);
		world->Vertices->Add(gcnew DVertex(Fixed::FromInt(x),Fixed::FromInt(y)));
	}
}

extern "C" vertex_t *P_GetVertex(int i)
{
	return ((DVertex^)world->Vertices[i])->ptr;
}

extern "C" int P_CountVertexes()
{
	return world->Vertices->Count;
}

extern "C" void P_LoadSectors(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 26;
	if (data->Length % 26)
		Core::Console->LogWarning("This map's SECTORS lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		char flatname[8];
		DSector^ sector = gcnew DSector();
		sector->FloorZ = Fixed::FromInt(BitConv::FromInt16(data,i * 26 + 0));
		sector->CeilingZ = Fixed::FromInt(BitConv::FromInt16(data,i * 26 + 2));
		Marshal::Copy(data,i * 26 + 4,(IntPtr)flatname,8);
		sector->ptr->floorpic = R_FlatNumForName(flatname);
		Marshal::Copy(data,i * 26 + 12,(IntPtr)flatname,8);
		sector->ptr->ceilingpic = R_FlatNumForName(flatname);
		sector->LightLevel = BitConv::FromInt16(data,i * 26 + 20);
		sector->Special = BitConv::FromInt16(data,i * 26 + 22);
		sector->Tag = BitConv::FromInt16(data,i * 26 + 24);
		world->Sectors->Add(sector);
	}
}

extern "C" sector_t *P_GetSector(int i)
{
	return ((DSector^)world->Sectors[i])->ptr;
}

extern "C" int P_CountSectors()
{
	return world->Sectors->Count;
}

extern "C" int P_UngetSector(sector_t *ptr)
{
	return world->Sectors->IndexOf(DSector::FromPtr(ptr));
}

extern "C" void P_LoadSideDefs(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 30;
	if (data->Length % 30)
		Core::Console->LogWarning("This map's SIDEDEFS lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		char texturename[8];
		int sectornum = (unsigned short)BitConv::FromInt16(data,i * 30 + 28);
		if (sectornum >= world->Sectors->Count)
		{
			Core::Console->LogError("Sidedef {0} references a non-existent sector.",i);
			I_Error("Bad sidedef->sector reference");
		}
		DSidedef^ sidedef = gcnew DSidedef((DSector^)world->Sectors[sectornum]);
		sidedef->XOffset = Fixed::FromInt(BitConv::FromInt16(data,i * 30 + 0));
		sidedef->YOffset = Fixed::FromInt(BitConv::FromInt16(data,i * 30 + 2));
		Marshal::Copy(data,i * 30 + 4,(IntPtr)texturename,8);
		sidedef->ptr->toptexture = R_TextureNumForName(texturename);
		Marshal::Copy(data,i * 30 + 12,(IntPtr)texturename,8);
		sidedef->ptr->bottomtexture = R_TextureNumForName(texturename);
		Marshal::Copy(data,i * 30 + 20,(IntPtr)texturename,8);
		sidedef->ptr->midtexture = R_TextureNumForName(texturename);
		world->Sidedefs->Add(sidedef);
	}
}

extern "C" side_t *P_GetSideDef(int i)
{
	return ((DSidedef^)world->Sidedefs[i])->ptr;
}

extern "C" int P_CountSideDefs()
{
	return world->Sidedefs->Count;
}
