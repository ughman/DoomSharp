#ifndef __P_MOBJ_HPP__
#define __P_MOBJ_HPP__

#include "p_tick.hpp"

extern "C"
{
#include "doomstat.h"
#include "m_random.h"
#include "p_local.h"
}

extern mobjtype_t P_GetActorType(Type^ type);

ref class Actor : LegacyThinker
{
private:
	Object^ species;
public:
	mobj_t *mobj;

	Actor(fixed_t x,fixed_t y,fixed_t z) : LegacyThinker(sizeof(mobj_t))
	{
		mobj = (mobj_t *)ptr;
		memset(mobj,0,sizeof(mobj_t));
		mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
		mobj->x = x;
		mobj->y = y;
		mobj->z = z;
		mobj->lastlook = P_Random() % MAXPLAYERS;
		species = GetType();
	}

	property Object^ Species
	{
		Object^ get() { return species; }
		void set(Object^ value) { species = value; }
	}
};

ref class LegacyActor : Actor
{
public:
	LegacyActor(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type) : Actor(x,y,z)
	{
		Species = (int)type;
		mobjinfo_t &info = mobjinfo[type];
		mobj->type = type;
		mobj->info = &info;
		mobj->radius = info.radius;
		mobj->height = info.height;
		mobj->flags = info.flags;
		mobj->health = info.spawnhealth;
		mobj->reactiontime = info.reactiontime;
		state_t &state = states[info.spawnstate];
		mobj->state = &state;
		mobj->tics = state.tics;
		mobj->sprite = state.sprite;
		mobj->frame = state.frame;
	}
};

extern Actor^ P_MobjToActor(mobj_t *mobj);

#endif
