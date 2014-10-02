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

	DVertex(::World^ world,Fixed x,Fixed y) : Vertex(world,x,y)
	{
		ptr = new vertex_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->x = x.Value;
		ptr->y = y.Value;
	}

	virtual property Fixed x
	{
		Fixed get() override { return Fixed(ptr->x); }
		void set(Fixed value) override { ptr->x = value.Value; }
	}

	virtual property Fixed y
	{
		Fixed get() override { return Fixed(ptr->y); }
		void set(Fixed value) override { ptr->y = value.Value; }
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

	DSector(::World^ world) : Sector(world)
	{
		ptr = new sector_t;
		memset(ptr,0,sizeof(sector_t));
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->lightlevel = 160;
	}

	virtual property Fixed floorz
	{
		Fixed get() override { return Fixed(ptr->floorheight); }
		void set(Fixed value) override { ptr->floorheight = value.Value; }
	}

	virtual property Fixed ceilingz
	{
		Fixed get() override { return Fixed(ptr->ceilingheight); }
		void set(Fixed value) override { ptr->ceilingheight = value.Value; }
	}

	virtual property int lightlevel
	{
		int get() override { return ptr->lightlevel; }
		void set(int value) override { ptr->lightlevel = value; }
	}

	virtual property int special
	{
		int get() override { return ptr->special; }
		void set(int value) override { ptr->special = value; }
	}

	virtual property int tag
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

	DSidedef(::World^ world,DSector^ sector) : Sidedef(world,sector)
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

	virtual property DoomSharp::Sector^ sector
	{
		DoomSharp::Sector^ get() override { return DSector::FromPtr(ptr->sector); }
		void set(DoomSharp::Sector^ value) override { ptr->sector = ((DSector^)value)->ptr; }
	}

	virtual property Fixed xoffset
	{
		Fixed get() override { return Fixed(ptr->textureoffset); }
		void set(Fixed value) override { ptr->textureoffset = value.Value; }
	}

	virtual property Fixed yoffset
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

	DLinedef(::World^ world,DVertex^ start,DVertex^ end,DSidedef^ front,DSidedef^ back) : Linedef(world,start,end,front,back)
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

	virtual property Vertex^ start
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v1); }
		void set(Vertex^ value) override { ptr->v1 = ((DVertex^)value)->ptr; }
	}

	virtual property Vertex^ end
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v2); }
		void set(Vertex^ value) override { ptr->v2 = ((DVertex^)value)->ptr; }
	}

	virtual property Sidedef^ front
	{
		Sidedef^ get() override { return DSidedef::FromPtr(ptr->side[0]); }
		void set(Sidedef^ value) override { ptr->side[0] = ((DSidedef^)value)->ptr; }
	}

	virtual property Sidedef^ back
	{
		Sidedef^ get() override { return DSidedef::FromPtr(ptr->side[1]); }
		void set(Sidedef^ value) override { ptr->side[1] = ((DSidedef^)value)->ptr; }
	}

	virtual property int special
	{
		int get() override { return ptr->special; }
		void set(int value) override { ptr->special = value; }
	}

	virtual property int tag
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

ref class DThing : Thing
{
public:
	static DThing^ FromPtr(mapthing_t *ptr)
	{
		return ptr ? (DThing^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	mapthing_t *ptr;

	DThing(::World^ world) : Thing(world)
	{
		ptr = new mapthing_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->x = 0;
		ptr->y = 0;
		ptr->angle = 0;
		ptr->type = 0;
		ptr->options = 0;
	}

	virtual property Fixed x
	{
		Fixed get() override { return Fixed::FromInt(ptr->x); }
		void set(Fixed value) override { ptr->x = value.IntValue; }
	}

	virtual property Fixed y
	{
		Fixed get() override { return Fixed(ptr->y); }
		void set(Fixed value) override { ptr->y = value.IntValue; }
	}

	virtual property int angle
	{
		int get() override { return ptr->angle; }
		void set(int value) override { ptr->angle = value; }
	}

	virtual property int doomednum
	{
		int get() override { return ptr->type; }
		void set(int value) override { ptr->type = value; }
	}

	~DThing()
	{
		this->!DThing();
	}

	!DThing()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

ref class DSeg : Seg
{
public:
	static DSeg^ FromPtr(seg_t *ptr)
	{
		return ptr ? (DSeg^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	seg_t *ptr;

	DSeg(::World^ world,DVertex^ start,DVertex^ end,DLinedef^ linedef,bool isbackside,::Angle angle,Fixed offset) : Seg(world,start,end,linedef,isbackside,angle,offset)
	{
		ptr = new seg_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->v1 = start->ptr;
		ptr->v2 = end->ptr;
		ptr->angle = angle.Value;
		ptr->offset = offset.Value;
		ptr->sidedef = linedef->ptr->side[isbackside];
		ptr->linedef = linedef->ptr;
		if (linedef->ptr->side[isbackside])
			ptr->frontsector = linedef->ptr->side[isbackside]->sector;
		else
			ptr->frontsector = NULL;
		if (linedef->ptr->side[!isbackside] && (linedef->ptr->flags & ML_TWOSIDED))
			ptr->backsector = linedef->ptr->side[!isbackside]->sector;
		else
			ptr->backsector = NULL;
	}

	virtual property Vertex^ start
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v1); }
		void set(Vertex^ value) override { ptr->v1 = ((DVertex^)value)->ptr; }
	}

	virtual property Vertex^ end
	{
		Vertex^ get() override { return DVertex::FromPtr(ptr->v2); }
		void set(Vertex^ value) override { ptr->v2 = ((DVertex^)value)->ptr; }
	}

	virtual property DoomSharp::Linedef^ linedef
	{
		DoomSharp::Linedef^ get() override { return DLinedef::FromPtr(ptr->linedef); }
		void set(DoomSharp::Linedef^ value) override { ptr->linedef = ((DLinedef^)value)->ptr; }
	}

	virtual property ::Angle angle
	{
		::Angle get() override { return ::Angle(ptr->angle); }
		void set(::Angle value) override { ptr->angle = value.Value; }
	}

	virtual property Fixed offset
	{
		Fixed get() override { return Fixed(ptr->offset); }
		void set(Fixed value) override { ptr->offset = value.Value; }
	}

	~DSeg()
	{
		this->!DSeg();
	}

	!DSeg()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

ref class DSubsector : Subsector
{
public:
	static DSubsector^ FromPtr(subsector_t *ptr)
	{
		return ptr ? (DSubsector^)GCHandle::FromIntPtr((IntPtr)ptr->handle).Target : nullptr;
	}

	subsector_t *ptr;

	DSubsector(::World^ world,::Sector^ sector) : Subsector(world,sector)
	{
		ptr = new subsector_t;
		ptr->handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		ptr->sector = ((DSector^)sector)->ptr;
	}

	~DSubsector()
	{
		this->!DSubsector();
	}

	!DSubsector()
	{
		GCHandle::FromIntPtr((IntPtr)ptr->handle).Free();
		delete ptr;
	}
};

#endif
