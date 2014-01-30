using namespace DoomSharp;

extern "C"
{
#include "p_mobj.h"
}

#include "p_mobj.hpp"

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

extern "C" mobj_t *P_SpawnMobj(fixed_t x,fixed_t y,fixed_t z,mobjtype_t type)
{
	LegacyActor^ actor = gcnew LegacyActor(x,y,z,type);
	thinkers->Add(actor);
	return actor->mobj;
}
