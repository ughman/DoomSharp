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

	virtual property Fixed X
	{
		Fixed get() override { return Fixed(mobj->x); }
		void set(Fixed value) override { mobj->x = value.Value; }
	}

	virtual property Fixed Y
	{
		Fixed get() override { return Fixed(mobj->y); }
		void set(Fixed value) override { mobj->y = value.Value; }
	}

	virtual property Fixed Z
	{
		Fixed get() override { return Fixed(mobj->z); }
		void set(Fixed value) override { mobj->z = value.Value; }
	}

	virtual property unsigned int Angle
	{
		unsigned int get() override { return mobj->angle; }
		void set(unsigned int value) override { mobj->angle = value; }
	}

	virtual property int SpriteNum
	{
		int get() override { return mobj->sprite; }
		void set(int value) override { mobj->sprite = (spritenum_t)value; }
	}

	virtual property int SpriteFrame
	{
		int get() override { return mobj->frame; }
		void set(int value) override { mobj->frame = value; }
	}

	virtual property Fixed Radius
	{
		Fixed get() override { return Fixed(mobj->radius); }
		void set(Fixed value) override { mobj->radius = value.Value; }
	}

	virtual property Fixed Height
	{
		Fixed get() override { return Fixed(mobj->height); }
		void set(Fixed value) override { mobj->height = value.Value; }
	}

	virtual property Fixed XMomentum
	{
		Fixed get() override { return Fixed(mobj->momx); }
		void set(Fixed value) override { mobj->momx = value.Value; }
	}

	virtual property Fixed YMomentum
	{
		Fixed get() override { return Fixed(mobj->momy); }
		void set(Fixed value) override { mobj->momy = value.Value; }
	}

	virtual property Fixed ZMomentum
	{
		Fixed get() override { return Fixed(mobj->momz); }
		void set(Fixed value) override { mobj->momz = value.Value; }
	}

	virtual property int Ticks
	{
		int get() override { return mobj->tics; }
		void set(int value) override { mobj->tics = value; }
	}

	virtual property int StateNum
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

	LEGACYFLAG(Special,MF_SPECIAL)
	LEGACYFLAG(Solid,MF_SOLID)
	LEGACYFLAG(Shootable,MF_SHOOTABLE)
	LEGACYFLAG(NoSector,MF_NOSECTOR)
	LEGACYFLAG(NoBlockmap,MF_NOBLOCKMAP)
	LEGACYFLAG(Ambush,MF_AMBUSH)
	LEGACYFLAG(JustHit,MF_JUSTHIT)
	LEGACYFLAG(JustAttacked,MF_JUSTATTACKED)
	LEGACYFLAG(SpawnCeiling,MF_SPAWNCEILING)
	LEGACYFLAG(NoGravity,MF_NOGRAVITY)
	LEGACYFLAG(DropOff,MF_DROPOFF)
	LEGACYFLAG(Pickup,MF_PICKUP)
	LEGACYFLAG(NoClip,MF_NOCLIP)
	LEGACYFLAG(Slide,MF_SLIDE)
	LEGACYFLAG(Float,MF_FLOAT)
	LEGACYFLAG(Teleport,MF_TELEPORT)
	LEGACYFLAG(Missile,MF_MISSILE)
	LEGACYFLAG(Dropped,MF_DROPPED)
	LEGACYFLAG(Shadow,MF_SHADOW)
	LEGACYFLAG(NoBlood,MF_NOBLOOD)
	LEGACYFLAG(Corpse,MF_CORPSE)
	LEGACYFLAG(InFloat,MF_INFLOAT)
	LEGACYFLAG(CountKill,MF_COUNTKILL)
	LEGACYFLAG(CountItem,MF_COUNTITEM)
	LEGACYFLAG(SkullFly,MF_SKULLFLY)
	LEGACYFLAG(NotDMatch,MF_NOTDMATCH)
#undef LEGACYFLAG

	virtual property int Health
	{
		int get() override { return mobj->health; }
		void set(int value) override { mobj->health = value; }
	}

	virtual property int MovementDirection
	{
		int get() override { return mobj->movedir; }
		void set(int value) override { mobj->movedir = value; }
	}

	virtual property int MovementCount
	{
		int get() override { return mobj->movecount; }
		void set(int value) override { mobj->movecount = value; }
	}

	virtual property Actor^ Target
	{
		Actor^ get() override { return FromPtr(mobj->target); }
		void set(Actor^ value) override { mobj->target = value ? ((DActor^)value)->mobj : NULL; }
	}

	virtual property int ReactionTime
	{
		int get() override { return mobj->reactiontime; }
		void set(int value) override { mobj->reactiontime = value; }
	}

	virtual property int LastLook
	{
		int get() override { return mobj->lastlook; }
		void set(int value) override { mobj->lastlook = value; }
	}

	virtual property Actor^ Tracer
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
