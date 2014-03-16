#ifndef __P_TICK_HPP__
#define __P_TICK_HPP__

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace DoomSharp;

#include <vcclr.h>
#include <stdlib.h>

extern "C"
{
#include "d_think.h"
}

extern gcroot<World^> world;

ref class LegacyThinker : Thinker
{
public:
	static LegacyThinker^ FromPtr(thinker_t *ptr)
	{
		return ptr ? (LegacyThinker^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	thinker_t *ptr;

	LegacyThinker(size_t size) : Thinker(::world)
	{
		ptr = (thinker_t *)malloc(size + 256);
		if (!ptr)
			throw gcnew ApplicationException();
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
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
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		free(ptr);
	}
};

#endif
