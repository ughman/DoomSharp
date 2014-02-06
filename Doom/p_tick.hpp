#ifndef __P_TICK_HPP__
#define __P_TICK_HPP__

using namespace System;
using namespace System::Collections::Generic;
using namespace DoomSharp;

#include <vcclr.h>
#include <stdlib.h>

extern "C"
{
#include "d_think.h"
}

extern int P_FindLegacyThinker(thinker_t *ptr);

extern gcroot<List<Thinker^>^> thinkers;

ref class LegacyThinker : Thinker
{
	static LegacyThinker()
	{
		legacythinkers = gcnew Dictionary<IntPtr,LegacyThinker^>();
	}
public:
	static Dictionary<IntPtr,LegacyThinker^>^ legacythinkers;
	thinker_t *ptr;

	LegacyThinker(size_t size)
	{
		ptr = (thinker_t *)malloc(size + 256);
		if (!ptr)
			throw gcnew ApplicationException();
		legacythinkers->Add((IntPtr)ptr,this);
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
		legacythinkers->Remove((IntPtr)ptr);
	}
};

extern LegacyThinker^ P_GetLegacyThinker(thinker_t *ptr);

#endif
