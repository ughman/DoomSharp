#ifndef __P_SETUP_HPP__
#define __P_SETUP_HPP__

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DoomSharp;

extern "C"
{
#include "r_defs.h"
}

#include <vcclr.h>

extern gcroot<World^> world;

ref class DVertex : Vertex
{
public:
	static DVertex^ FromPtr(vertex_t *ptr)
	{
		return ptr ? (DVertex^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	vertex_t *ptr;

	DVertex(Fixed x,Fixed y) : Vertex(x,y)
	{
		ptr = new vertex_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->x = x.Value;
		ptr->y = y.Value;
	}

	virtual property Fixed X
	{
		Fixed get() override { return Fixed(ptr->x); }
	}

	virtual property Fixed Y
	{
		Fixed get() override { return Fixed(ptr->y); }
	}

	~DVertex()
	{
		this->!DVertex();
	}

	!DVertex()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

#endif
