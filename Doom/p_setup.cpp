#include "p_setup.hpp"
#include "p_mobj.hpp"

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
		world->Vertices->Add(gcnew DVertex(world,Fixed::FromInt(x),Fixed::FromInt(y)));
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
		DSector^ sector = gcnew DSector(world);
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
		DSidedef^ sidedef = gcnew DSidedef(world,(DSector^)world->Sectors[sectornum]);
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

extern "C" void P_LoadLineDefs(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 14;
	if (data->Length % 14)
		Core::Console->LogWarning("This map's LINEDEFS lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		int startnum = (unsigned short)BitConv::FromInt16(data,i * 14 + 0);
		int endnum = (unsigned short)BitConv::FromInt16(data,i * 14 + 2);
		int frontnum = (unsigned short)BitConv::FromInt16(data,i * 14 + 10);
		int backnum = (unsigned short)BitConv::FromInt16(data,i * 14 + 12);
		if (startnum >= world->Vertices->Count)
		{
			Core::Console->LogError("Linedef {0} references a non-existent vertex.",i);
			I_Error("Bad linedef->vertex reference");
		}
		DVertex^ start = (DVertex^)world->Vertices[startnum];
		if (endnum >= world->Vertices->Count)
		{
			Core::Console->LogError("Linedef {0} references a non-existent vertex.",i);
			I_Error("Bad linedef->vertex reference");
		}
		DVertex^ end = (DVertex^)world->Vertices[endnum];
		DSidedef^ front;
		if (frontnum == 0xFFFF)
		{
			front = nullptr;
		}
		else if (frontnum >= world->Sidedefs->Count)
		{
			Core::Console->LogError("Linedef {0} references a non-existent sidedef.",i);
			front = nullptr;
		}
		else
		{
			front = (DSidedef^)world->Sidedefs[frontnum];
		}
		DSidedef^ back;
		if (backnum == 0xFFFF)
		{
			back = nullptr;
		}
		else if (backnum >= world->Sidedefs->Count)
		{
			Core::Console->LogError("Linedef {0} references a non-existent sidedef.",i);
			back = nullptr;
		}
		else
		{
			back = (DSidedef^)world->Sidedefs[backnum];
		}
		DLinedef^ linedef = gcnew DLinedef(world,start,end,front,back);
		linedef->ptr->flags = BitConv::FromInt16(data,i * 14 + 4);
		linedef->Special = BitConv::FromInt16(data,i * 14 + 6);
		linedef->Tag = BitConv::FromInt16(data,i * 14 + 8);
		world->Linedefs->Add(linedef);
	}
}

extern "C" line_t *P_GetLineDef(int i)
{
	return ((DLinedef^)world->Linedefs[i])->ptr;
}

extern "C" int P_CountLineDefs()
{
	return world->Linedefs->Count;
}

extern "C" int P_UngetLineDef(line_t *ptr)
{
	return world->Linedefs->IndexOf(DLinedef::FromPtr(ptr));
}

extern "C" void P_LoadThings(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 10;
	if (data->Length % 10)
		Core::Console->LogWarning("This map's THINGS lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		DThing^ thing = gcnew DThing(world);
		thing->X = Fixed::FromInt(BitConv::FromInt16(data,i * 10 + 0));
		thing->Y = Fixed::FromInt(BitConv::FromInt16(data,i * 10 + 2));
		thing->Angle = BitConv::FromInt16(data,i * 10 + 4);
		thing->DoomedNum = BitConv::FromInt16(data,i * 10 + 6);
		thing->ptr->options = BitConv::FromInt16(data,i * 10 + 8);
		world->Things->Add(thing);
	}
}

extern "C" void P_SpawnMapThing(mapthing_t *mthing);
extern "C" void P_SpawnThings()
{
	for each (DThing^ thing in world->Things)
	{
		P_SpawnMapThing(thing->ptr);
	}
}

extern "C" void P_LoadBlockMap(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 2;
	if (data->Length % 2)
		Core::Console->LogWarning("This map's BLOCKMAP lump has an irregular length.");
	if (data->Length < 8)
		I_Error("Blockmap invalid");
	Fixed xoffset = Fixed::FromInt(BitConv::FromInt16(data,0));
	Fixed yoffset = Fixed::FromInt(BitConv::FromInt16(data,2));
	int width = (unsigned short)BitConv::FromInt16(data,4);
	int height = (unsigned short)BitConv::FromInt16(data,6);
	if (count < 4 + width * height)
		I_Error("Blockmap too short");
	Blockmap^ blockmap = gcnew Blockmap(world,xoffset,yoffset,width,height);
	for (int x = 0;x < width;x++)
	{
		for (int y = 0;y < height;y++)
		{
			Block^ block = blockmap[x,y];
			int offset = x + y * width + 4;
			if (offset >= count)
				I_Error("Blockmap block offset out-of-bounds");
			for (int i = (unsigned short)BitConv::FromInt16(data,offset * 2);;i++)
			{
				if (i >= count)
					I_Error("Blockmap block lines out-of-bounds");
				int lineid = (unsigned short)BitConv::FromInt16(data,i * 2);
				if (lineid == 0xFFFF)
					break;
				if (lineid >= world->Linedefs->Count)
				{
					Core::Console->LogError("The linedef list for block ({0},{1}) references a non-existent linedef.",x,y);
					continue;
				}
				block->AddLinedef(world->Linedefs[lineid]);
			}
		}
	}
	world->Blockmap = blockmap;
}

extern "C" fixed_t P_GetBlockmapXOffset()
{
	return world->Blockmap->XOffset.Value;
}

extern "C" fixed_t P_GetBlockmapYOffset()
{
	return world->Blockmap->YOffset.Value;
}

extern "C" int P_GetBlockmapWidth()
{
	return world->Blockmap->Width;
}

extern "C" int P_GetBlockmapHeight()
{
	return world->Blockmap->Height;
}

extern "C" void P_BlockActorAdd(int x,int y,mobj_t *mobj)
{
	world->Blockmap[x,y]->AddActor(DActor::FromPtr(mobj));
}

extern "C" void P_BlockActorRemove(int x,int y,mobj_t *mobj)
{
	world->Blockmap[x,y]->RemoveActor(DActor::FromPtr(mobj));
}
