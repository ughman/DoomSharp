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

mobj_t *P_NewActor2()
{
	Actor^ actor = gcnew Actor();
	thinkers->Add(actor);
	return actor->mobj;
}

extern "C" mobj_t *P_NewActor()
{
	return P_NewActor2();
}

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
	}
};

Actor^ P_MobjToActor(mobj_t *mobj)
{
	return (Actor^)thinkers->default[P_FindLegacyThinker(&mobj->thinker)];
}
