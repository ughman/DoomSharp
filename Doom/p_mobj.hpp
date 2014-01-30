#ifndef __P_MOBJ_HPP__
#define __P_MOBJ_HPP__

#include "p_tick.hpp"

extern "C"
{
#include "doomstat.h"
#include "m_random.h"
#include "p_local.h"
}

ref class Actor : LegacyThinker
{
public:
	mobj_t *mobj;

	Actor() : LegacyThinker(sizeof(mobj_t))
	{
		mobj = (mobj_t *)ptr;
		memset(mobj,0,sizeof(mobj_t));
	}
};

ref class LegacyActor : Actor
{
public:
	LegacyActor(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
	{
		mobjinfo_t &info = mobjinfo[type];
		mobj->type = type;
		mobj->info = &info;
		mobj->x = x;
		mobj->y = y;
		mobj->radius = info.radius;
		mobj->height = info.height;
		mobj->flags = info.flags;
		mobj->health = info.spawnhealth;
		if (gameskill != sk_nightmare)
			mobj->reactiontime = info.reactiontime;
		mobj->lastlook = P_Random() % MAXPLAYERS;
		state_t &state = states[info.spawnstate];
		mobj->state = &state;
		mobj->tics = state.tics;
		mobj->sprite = state.sprite;
		mobj->frame = state.frame;
		P_SetThingPosition(mobj);
		mobj->floorz = mobj->subsector->sector->floorheight;
		mobj->ceilingz = mobj->subsector->sector->ceilingheight;
		if (z == ONFLOORZ)
			mobj->z = mobj->floorz;
		else if (z == ONCEILINGZ)
			mobj->z = mobj->ceilingz;
		else
			mobj->z = z;
		mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
	}
};

#endif
