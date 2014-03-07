#ifndef __P_SETUP_HPP__
#define __P_SETUP_HPP__

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DoomSharp;

extern "C"
{
#include "r_defs.h"
#include "r_data.h"
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

ref class DSector : Sector
{
public:
	static DSector^ FromPtr(sector_t *ptr)
	{
		return ptr ? (DSector^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	sector_t *ptr;

	DSector()
	{
		ptr = new sector_t;
		memset(ptr,0,sizeof(sector_t));
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->lightlevel = 160;
	}

	virtual property Fixed FloorZ
	{
		Fixed get() override { return Fixed(ptr->floorheight); }
		void set(Fixed value) override { ptr->floorheight = value.Value; }
	}

	virtual property Fixed CeilingZ
	{
		Fixed get() override { return Fixed(ptr->ceilingheight); }
		void set(Fixed value) override { ptr->ceilingheight = value.Value; }
	}

	virtual property int LightLevel
	{
		int get() override { return ptr->lightlevel; }
		void set(int value) override { ptr->lightlevel = value; }
	}

	virtual property int Special
	{
		int get() override { return ptr->special; }
		void set(int value) override { ptr->special = value; }
	}

	virtual property int Tag
	{
		int get() override { return ptr->tag; }
		void set(int value) override { ptr->tag = value; }
	}

	~DSector()
	{
		this->!DSector();
	}

	!DSector()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

#endif
