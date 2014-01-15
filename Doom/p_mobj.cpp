using namespace DoomSharp;

extern "C"
{
#include "p_mobj.h"
}

#include "p_tick.hpp"

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
