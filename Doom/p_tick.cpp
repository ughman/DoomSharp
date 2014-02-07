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
#include "gcweakref.hpp"
#include <map>

gcroot<List<Thinker^>^> thinkers;

int P_FindLegacyThinker(thinker_t *ptr)
{
	for (int i = 0;i < thinkers->Count;i++)
	{
		Thinker^ thinker = thinkers->default[i];
		if (dynamic_cast<LegacyThinker^>(thinker))
		{
			if (((LegacyThinker^)thinker)->ptr == ptr)
			{
				return i;
			}
		}
	}
	I_Error("P_FindLegacyThinker: Couldn't find thinker!");
	throw gcnew Exception();
}

std::map<thinker_t *,gcweakref<LegacyThinker^>> legacythinkers;

void LegacyThinker::AddLegacyThinker(thinker_t *a,LegacyThinker^ b)
{
	legacythinkers[a] = b;
}

void LegacyThinker::RemoveLegacyThinker(thinker_t *a)
{
	legacythinkers[a] = (LegacyThinker^)nullptr;
}

LegacyThinker^ P_GetLegacyThinker(thinker_t *ptr)
{
	if (!ptr)
		return nullptr;
	return legacythinkers[ptr];
}

extern "C" void P_InitThinkers()
{
	thinkers = gcnew List<Thinker^>();
}

extern "C" thinker_t *P_NewThinker(size_t size)
{
	LegacyThinker ^thinker = gcnew LegacyThinker(size);
	thinkers->Add(thinker);
	return thinker->ptr;
}

extern "C" void P_RemoveThinker(thinker_t *thinker)
{
	thinker->function.acv = (actionf_v)-1;
}

extern "C" thinker_t *P_FirstThinker()
{
	for (int i = 0;i < thinkers->Count;i++)
	{
		Thinker^ thinker = thinkers->default[i];
		if (dynamic_cast<LegacyThinker^>(thinker))
		{
			return ((LegacyThinker^)thinker)->ptr;
		}
	}
	return NULL;
}

extern "C" thinker_t *P_NextThinker(thinker_t *it)
{
	for (int i = P_FindLegacyThinker(it) + 1;i < thinkers->Count;i++)
	{
		Thinker^ thinker = thinkers->default[i];
		if (dynamic_cast<LegacyThinker^>(thinker))
		{
			return ((LegacyThinker^)thinker)->ptr;
		}
	}
	return NULL;
}

extern "C" void P_RunThinkers()
{
	for (int i = 0;i < thinkers->Count;i++)
	{
		Thinker^ thinker = thinkers->default[i];
		if (thinker->Tick())
		{
			thinkers->RemoveAt(i);
			i--;
		}
	}
}

void P_AddManagedThinker(Thinker^ thinker)
{
	thinkers->Add(thinker);
}
