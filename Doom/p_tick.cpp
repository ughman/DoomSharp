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

ref class LegacyThinker : Thinker
{
public:
	thinker_t *ptr;

	LegacyThinker(size_t size)
	{
		ptr = (thinker_t *)malloc(size + 256);
		if (!ptr)
			throw gcnew ApplicationException();
	}

	virtual bool Tick() override
	{
		if (ptr->function.acp1 == (actionf_p1)-1)
		{
			return true;
		}
		if (ptr->function.acp1)
		{
			ptr->function.acp1(ptr);
		}
		return false;
	}

	~LegacyThinker()
	{
		this->!LegacyThinker();
	}

	!LegacyThinker()
	{
		free(ptr);
	}
};

gcroot<List<Thinker^>^> thinkers;

int P_FindLegacyThinker(thinker_t *ptr)
{
	for (int i = 0;i < thinkers->Count;i++)
	{
		Thinker^ thinker = thinkers->default[i];
		if (thinker->GetType() == LegacyThinker::typeid)
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
		if (thinker->GetType() == LegacyThinker::typeid)
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
		if (thinker->GetType() == LegacyThinker::typeid)
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
