#ifndef __P_MOBJ_HPP__
#define __P_MOBJ_HPP__

#include "p_tick.hpp"

extern "C"
{
#include "doomstat.h"
#include "m_random.h"
#include "p_local.h"
#include "sounds.h"
}

extern mobjtype_t P_GetActorType(Type^ type);

ref class DActor : Actor
{
public:
	static DActor^ FromPtr(mobj_t *ptr)
	{
		return ptr ? (DActor^)GCHandle::FromIntPtr((IntPtr)ptr->thinker.handle).Target : nullptr;
	}

	mobj_t *mobj;

	DActor() : Actor(::world)
	{
		mobj = new mobj_t;
		memset(mobj,0,sizeof(mobj_t));
		mobj->thinker.handle = (void *)GCHandle::ToIntPtr(GCHandle::Alloc(this,GCHandleType::Weak));
		mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
		mobj->type = P_GetActorType(GetType());
		X = Fixed::Zero;
		Y = Fixed::Zero;
		Z = Fixed::Zero;
		Radius = Fixed::FromInt(20);
		Height = Fixed::FromInt(16);
		mobj->flags = 0;
		Health = 1000;
		ReactionTime = 8;
	}

	virtual property Fixed x
	{
		Fixed get() override { return Fixed(mobj->x); }
		void set(Fixed value) override { mobj->x = value.Value; }
	}

	virtual property Fixed y
	{
		Fixed get() override { return Fixed(mobj->y); }
		void set(Fixed value) override { mobj->y = value.Value; }
	}

	virtual property Fixed z
	{
		Fixed get() override { return Fixed(mobj->z); }
		void set(Fixed value) override { mobj->z = value.Value; }
	}

	virtual property unsigned int angle
	{
		unsigned int get() override { return mobj->angle; }
		void set(unsigned int value) override { mobj->angle = value; }
	}

	virtual property int spritenum
	{
		int get() override { return mobj->sprite; }
		void set(int value) override { mobj->sprite = (spritenum_t)value; }
	}

	virtual property int spriteframe
	{
		int get() override { return mobj->frame; }
		void set(int value) override { mobj->frame = value; }
	}

	virtual property Fixed radius
	{
		Fixed get() override { return Fixed(mobj->radius); }
		void set(Fixed value) override { mobj->radius = value.Value; }
	}

	virtual property Fixed height
	{
		Fixed get() override { return Fixed(mobj->height); }
		void set(Fixed value) override { mobj->height = value.Value; }
	}

	virtual property Fixed xmomentum
	{
		Fixed get() override { return Fixed(mobj->momx); }
		void set(Fixed value) override { mobj->momx = value.Value; }
	}

	virtual property Fixed ymomentum
	{
		Fixed get() override { return Fixed(mobj->momy); }
		void set(Fixed value) override { mobj->momy = value.Value; }
	}

	virtual property Fixed zmomentum
	{
		Fixed get() override { return Fixed(mobj->momz); }
		void set(Fixed value) override { mobj->momz = value.Value; }
	}

	virtual property int ticks
	{
		int get() override { return mobj->tics; }
		void set(int value) override { mobj->tics = value; }
	}

	virtual property int statenum
	{
		int get() override { return mobj->state - ::states; }
		void set(int value) override { mobj->state = &::states[value]; }
	}

#define LEGACYFLAG(propname,legacyname) \
	virtual property bool propname \
	{ \
		bool get() override { return mobj->flags & legacyname; } \
		void set(bool value) override \
		{ \
			if (value) \
				mobj->flags |= legacyname; \
			else \
				mobj->flags &= ~legacyname; \
		} \
	}

	LEGACYFLAG(special,MF_SPECIAL)
	LEGACYFLAG(solid,MF_SOLID)
	LEGACYFLAG(shootable,MF_SHOOTABLE)
	LEGACYFLAG(nosector,MF_NOSECTOR)
	LEGACYFLAG(noblockmap,MF_NOBLOCKMAP)
	LEGACYFLAG(ambush,MF_AMBUSH)
	LEGACYFLAG(justhit,MF_JUSTHIT)
	LEGACYFLAG(justattacked,MF_JUSTATTACKED)
	LEGACYFLAG(spawnceiling,MF_SPAWNCEILING)
	LEGACYFLAG(nogravity,MF_NOGRAVITY)
	LEGACYFLAG(dropoff,MF_DROPOFF)
	LEGACYFLAG(pickup,MF_PICKUP)
	LEGACYFLAG(noclip,MF_NOCLIP)
	LEGACYFLAG(slide,MF_SLIDE)
	LEGACYFLAG(floats,MF_FLOAT)
	LEGACYFLAG(teleport,MF_TELEPORT)
	LEGACYFLAG(missile,MF_MISSILE)
	LEGACYFLAG(dropped,MF_DROPPED)
	LEGACYFLAG(shadow,MF_SHADOW)
	LEGACYFLAG(noblood,MF_NOBLOOD)
	LEGACYFLAG(corpse,MF_CORPSE)
	LEGACYFLAG(infloat,MF_INFLOAT)
	LEGACYFLAG(countkill,MF_COUNTKILL)
	LEGACYFLAG(countitem,MF_COUNTITEM)
	LEGACYFLAG(skullfly,MF_SKULLFLY)
	LEGACYFLAG(notdmatch,MF_NOTDMATCH)
#undef LEGACYFLAG

	virtual property int health
	{
		int get() override { return mobj->health; }
		void set(int value) override { mobj->health = value; }
	}

	virtual property int movementdirection
	{
		int get() override { return mobj->movedir; }
		void set(int value) override { mobj->movedir = value; }
	}

	virtual property int movementcount
	{
		int get() override { return mobj->movecount; }
		void set(int value) override { mobj->movecount = value; }
	}

	virtual property Actor^ target
	{
		Actor^ get() override { return FromPtr(mobj->target); }
		void set(Actor^ value) override { mobj->target = value ? ((DActor^)value)->mobj : NULL; }
	}

	virtual property int reactiontime
	{
		int get() override { return mobj->reactiontime; }
		void set(int value) override { mobj->reactiontime = value; }
	}

	virtual property int lastlook
	{
		int get() override { return mobj->lastlook; }
		void set(int value) override { mobj->lastlook = value; }
	}

	virtual property Actor^ tracer
	{
		Actor^ get() override { return FromPtr(mobj->tracer); }
		void set(Actor^ value) override { mobj->tracer = value ? ((DActor^)value)->mobj : NULL; }
	}

	virtual bool Tick() override
	{
		if (mobj->thinker.function.acp1 == (actionf_p1)-1)
		{
			return true;
		}
		if (mobj->thinker.function.acp1)
		{
			mobj->thinker.function.acp1(mobj);
		}
		return false;
	}

	~DActor()
	{
		this->!DActor();
	}

	!DActor()
	{
		GCHandle::FromIntPtr((IntPtr)mobj->thinker.handle).Free();
		delete mobj;
	}
};

#endif
