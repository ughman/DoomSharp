using namespace System;
using namespace System::Collections::Generic;
using namespace DoomSharp;

extern "C"
{
#include "p_mobj.h"
}

#include <vcclr.h>
#include "p_mobj.hpp"

gcroot<List<Type^>^> actortypes;
gcroot<Dictionary<int,Type^>^> doomednumtable;

mobj_t *P_SpawnMobj2(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
{
	Actor^ actor;
	if (actortypes->default[type])
	{
		array<Object^>^ args = gcnew array<Object^>(3);
		args[0] = x;
		args[1] = y;
		args[2] = z;
		actor = (Actor^)Activator::CreateInstance(actortypes->default[type],args);
	}
	else
	{
		actor = gcnew LegacyActor(x,y,z,type);
	}
	P_SetThingPosition(actor->mobj);
	actor->mobj->floorz = actor->mobj->subsector->sector->floorheight;
	actor->mobj->ceilingz = actor->mobj->subsector->sector->ceilingheight;
	if (z == ONFLOORZ)
		actor->mobj->z = actor->mobj->floorz;
	else if (z == ONCEILINGZ)
		actor->mobj->z = actor->mobj->ceilingz;
	if (gameskill == sk_nightmare)
		actor->mobj->reactiontime = 0;
	actor->LastLook = P_Random() % MAXPLAYERS;
	actor->StateNum = actor->GetStateNum("Spawn");
	state_t &state = states[actor->StateNum];
	actor->Tics = state.tics;
	actor->SpriteNum = state.sprite;
	actor->SpriteFrame = state.frame;
	thinkers->Add(actor);
	return actor->mobj;
}

extern "C" mobj_t *P_SpawnMobj(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
{
	return P_SpawnMobj2(x,y,z,type);
}

static class InitActorTypeTable
{
public:
	InitActorTypeTable()
	{
		actortypes = gcnew List<Type^>(NUMMOBJTYPES);
		for (int i = 0;i < NUMMOBJTYPES;i++)
		{
			actortypes->Add(nullptr);
		}
		doomednumtable = gcnew Dictionary<int,Type^>();
	}
} initactortypetable;

ref class P_RegisterActorTypeClass
{
	[RegistrarTypeHandler]
	static void P_RegisterActorType(Type^ type)
	{
		if (!Actor::typeid->IsAssignableFrom(type))
			return;
		actortypes->Add(type);
		for each (ActorTypeAttribute^ attribute in type->GetCustomAttributes(ActorTypeAttribute::typeid,false))
		{
			actortypes->default[attribute->Value] = type;
		}
		for each (DoomedNumAttribute^ attribute in type->GetCustomAttributes(DoomedNumAttribute::typeid,false))
		{
			if (doomednumtable->ContainsKey(attribute->Value))
			{
				doomednumtable->default[attribute->Value] = type;
			}
			else
			{
				doomednumtable->Add(attribute->Value,type);
			}
		}
	}
};

Actor^ P_MobjToActor(mobj_t *mobj)
{
	if (!mobj)
		return nullptr;
	return (Actor^)thinkers->default[P_FindLegacyThinker(&mobj->thinker)];
}

Actor^ Actor::MobjToActor(mobj_t *mobj)
{
	return P_MobjToActor(mobj);
}

mobjtype_t P_GetActorType(Type^ type)
{
	return (mobjtype_t)actortypes->IndexOf(type);
}

extern "C" int P_LookupDoomedNum(int doomednum)
{
	if (doomednumtable->ContainsKey(doomednum))
	{
		return P_GetActorType(doomednumtable->default[doomednum]);
	}
	else
	{
		for (int i = 0;i < NUMMOBJTYPES;i++)
		{
			if (mobjinfo[i].doomednum == doomednum)
			{
				return i;
			}
		}
		return -1;
	}
}

extern "C" bool P_CheckSameSpecies(mobj_t *a,mobj_t *b)
{
	if (!a || !b)
	{
		return false;
	}
	Actor^ a2 = P_MobjToActor(a);
	Actor^ b2 = P_MobjToActor(b);
	return (a2->Species != nullptr && a2->Species->Equals(b2->Species));
}
