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
gcroot<Dictionary<int,Actor^>^> dummyactors;

Actor^ P_CreateActor(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
{
	Actor^ actor;
	Type^ actortype = actortypes->default[type];
	if (actortype)
	{
		array<Object^>^ args = gcnew array<Object^>(3);
		args[0] = x;
		args[1] = y;
		args[2] = z;
		actor = (Actor^)Activator::CreateInstance(actortype,args);
	}
	else
	{
		throw gcnew ApplicationException();
	}
	return actor;
}

mobj_t *P_SpawnMobj2(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
{
	Actor^ actor = P_CreateActor(x,y,z,type);
	P_SetThingPosition(actor->mobj);
	actor->mobj->floorz = actor->mobj->subsector->sector->floorheight;
	actor->mobj->ceilingz = actor->mobj->subsector->sector->ceilingheight;
	if (z == ONFLOORZ)
		actor->mobj->z = actor->mobj->floorz;
	else if (z == ONCEILINGZ)
		actor->mobj->z = actor->mobj->ceilingz;
	if (gameskill == sk_nightmare)
	{
		actor->mobj->reactiontime = 0;
		switch (actor->mobj->type)
		{
		case MT_BRUISERSHOT:
		case MT_HEADSHOT:
		case MT_TROOPSHOT:
			actor->Speed = Fixed::FromInt(20);
			break;
		}
	}
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
		dummyactors = gcnew Dictionary<int,Actor^>();
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
	return (Actor^)P_GetLegacyThinker(&mobj->thinker);
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
	Type^ type;
	if (doomednumtable->TryGetValue(doomednum,type))
	{
		return P_GetActorType(type);
	}
	else
	{
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

extern "C" int P_GetActorSpeed(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->Speed.Value;
}

extern "C" int P_GetActorMass(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->Mass;
}

extern "C" int P_GetActorDamage(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->Damage;
}

extern "C" int P_GetActorPainChance(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->PainChance;
}

extern "C" int P_GetActorSeeSound(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->SeeSoundNum;
}

extern "C" int P_GetActorActiveSound(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->ActiveSoundNum;
}

extern "C" int P_GetActorAttackSound(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->AttackSoundNum;
}

extern "C" int P_GetActorPainSound(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->PainSoundNum;
}

extern "C" int P_GetActorDeathSound(mobj_t *mobj)
{
	return P_MobjToActor(mobj)->DeathSoundNum;
}

extern "C" int P_GetActorStateNum(mobj_t *mobj,char *label)
{
	Actor^ actor = P_MobjToActor(mobj);
	String^ label2 = gcnew String(label);
	if (actor->HasState(label2))
	{
		return actor->GetStateNum(label2);
	}
	else
	{
		return S_NULL;
	}
}

extern "C" bool P_CheckMobjStateLabel(mobj_t *mobj,char *label)
{
	return P_MobjToActor(mobj)->HasState(gcnew String(label));
}

extern "C" bool P_CheckMobjStateLabelIs(mobj_t *mobj,char *label)
{
	Actor^ actor = P_MobjToActor(mobj);
	return actor->StateNum == actor->GetStateNum(gcnew String(label));
}

extern "C" void P_SetMobjStateLabel(mobj_t *mobj,char *label)
{
	int statenum = P_MobjToActor(mobj)->GetStateNum(gcnew String(label));
	P_SetMobjState(mobj,(statenum_t)statenum);
}

mobj_t *dummyactor;

extern "C" void P_SetDummyActor(mobjtype_t type)
{
	Actor^ actor;
	if (!dummyactors->TryGetValue(type,actor))
	{
		actor = P_CreateActor(0,0,0,type);
		dummyactors->Add(type,actor);
	}
	dummyactor = actor->mobj;
}
