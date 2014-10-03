#include "p_setup.hpp"
#include "p_mobj.hpp"

extern "C" int P_BlockLinesIterator(int x,int y,int (*func)(line_t *))
{
	if (x < 0 || x >= world->Blockmap->Width || y < 0 || y >= world->Blockmap->Height)
	{
		return true;
	}
	for each (DLinedef^ linedef in world->Blockmap[x,y]->Linedefs)
	{
		if (linedef->ptr->validcount == validcount)
			continue;
		linedef->ptr->validcount = validcount;
		if (!func(linedef->ptr))
			return false;
	}
	return true;
}

extern "C" int P_BlockThingsIterator(int x,int y,int (*func)(mobj_t *))
{
	if (x < 0 || x >= world->Blockmap->Width || y < 0 || y >= world->Blockmap->Height)
	{
		return true;
	}
	for each (DActor^ actor in world->Blockmap[x,y]->Actors)
	{
		if (!func(actor->mobj))
			return false;
	}
	return true;
}

extern "C" void P_SetThingPosition(mobj_t *thing)
{
	DActor::FromPtr(thing)->Link();
}

extern "C" void P_UnsetThingPosition(mobj_t *thing)
{
	DActor::FromPtr(thing)->Unlink();
}
