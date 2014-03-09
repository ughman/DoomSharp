using namespace System;
using namespace System::Collections::Generic;
using namespace DoomSharp;

extern "C"
{
#include "p_local.h"
#include "i_system.h"
}

#include <vcclr.h>
#include <stdlib.h>
#include "p_tick.hpp"
#include "p_mobj.hpp"

gcroot<World^> world;

extern "C" void P_InitWorld()
{
	world = gcnew World();
}

extern "C" thinker_t *P_NewThinker(size_t size)
{
	LegacyThinker ^thinker = gcnew LegacyThinker(size);
	world->AddThinker(thinker);
	return thinker->ptr;
}

extern "C" void P_RemoveThinker(thinker_t *thinker)
{
	thinker->function.acv = (actionf_v)-1;
}

extern "C" thinker_t *P_FirstThinker()
{
	for each (Thinker^ thinker in world->Thinkers)
	{
		if (dynamic_cast<DActor^>(thinker))
		{
			return (thinker_t *)((DActor^)thinker)->mobj;
		}
	}
	return NULL;
}

extern "C" thinker_t *P_NextThinker(thinker_t *it)
{
	bool found = false;
	for each (Thinker^ thinker in world->Thinkers)
	{
		if (dynamic_cast<DActor^>(thinker))
		{
			if (found)
			{
				return (thinker_t *)((DActor^)thinker)->mobj;
			}
			else if ((thinker_t *)((DActor^)thinker)->mobj == it)
			{
				found = true;
			}
		}
	}
	return NULL;
}

extern "C" void P_RunThinkers()
{
	world->Tick();
}
