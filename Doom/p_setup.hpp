#ifndef __P_SETUP_HPP__
#define __P_SETUP_HPP__

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DoomSharp;

extern "C"
{
#include "r_defs.h"
#include "r_data.h"
#include "m_bbox.h"
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

ref class DSidedef : Sidedef
{
public:
	static DSidedef^ FromPtr(side_t *ptr)
	{
		return ptr ? (DSidedef^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	side_t *ptr;

	DSidedef(DSector^ sector) : Sidedef(sector)
	{
		ptr = new side_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->sector = sector->ptr;
		ptr->textureoffset = 0;
		ptr->rowoffset = 0;
		ptr->toptexture = 0;
		ptr->bottomtexture = 0;
		ptr->midtexture = 0;
	}

	virtual property DoomSharp::Sector^ Sector
	{
		DoomSharp::Sector^ get() override { return DSector::FromPtr(ptr->sector); }
	}

	virtual property Fixed XOffset
	{
		Fixed get() override { return Fixed(ptr->textureoffset); }
		void set(Fixed value) override { ptr->textureoffset = value.Value; }
	}

	virtual property Fixed YOffset
	{
		Fixed get() override { return Fixed(ptr->rowoffset); }
		void set(Fixed value) override { ptr->rowoffset = value.Value; }
	}

	~DSidedef()
	{
		this->!DSidedef();
	}

	!DSidedef()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

ref class DLinedef : Linedef
{
public:
	static DLinedef^ FromPtr(line_t *ptr)
	{
		return ptr ? (DLinedef^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	line_t *ptr;

	DLinedef(DVertex^ start,DVertex^ end,DSidedef^ front,DSidedef^ back) : Linedef(start,end,front,back)
	{
		ptr = new line_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->v1 = start->ptr;
		ptr->v2 = end->ptr;
		ptr->side[0] = front ? front->ptr : NULL;
		ptr->side[1] = back ? back->ptr : NULL;
		ptr->flags = 0;
		ptr->special = 0;
		ptr->tag = 0;
		ptr->dx = ptr->v2->x - ptr->v1->x;
		ptr->dy = ptr->v2->y - ptr->v1->y;
		if (!ptr->dx)
			ptr->slopetype = ST_VERTICAL;
		else if (!ptr->dy)
			ptr->slopetype = ST_HORIZONTAL;
		else if (FixedDiv(ptr->dy,ptr->dx) > 0)
			ptr->slopetype = ST_POSITIVE;
		else
			ptr->slopetype = ST_NEGATIVE;
		ptr->bbox[BOXLEFT] = Math::Min(ptr->v1->x,ptr->v2->x);
		ptr->bbox[BOXRIGHT] = Math::Max(ptr->v1->x,ptr->v2->x);
		ptr->bbox[BOXBOTTOM] = Math::Min(ptr->v1->y,ptr->v2->y);
		ptr->bbox[BOXTOP] = Math::Max(ptr->v1->y,ptr->v2->y);
		ptr->frontsector = ptr->side[0] ? ptr->side[0]->sector : NULL;
		ptr->backsector = ptr->side[1] ? ptr->side[1]->sector : NULL;
	}

	virtual property Vertex^ Start
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v1); }
	}

	virtual property Vertex^ End
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v2); }
	}

	virtual property Sidedef^ Front
	{
		Sidedef^ get() override { return DSidedef::FromPtr(ptr->side[0]); }
	}

	virtual property Sidedef^ Back
	{
		Sidedef^ get() override { return DSidedef::FromPtr(ptr->side[1]); }
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

	~DLinedef()
	{
		this->!DLinedef();
	}

	!DLinedef()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

#endif
