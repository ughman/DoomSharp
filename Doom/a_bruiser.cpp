#include "p_mobj.hpp"

[ActorType(MT_BRUISER)]
ref class BaronOfHell : LegacyActor
{
public:
	BaronOfHell(fixed_t x,fixed_t y,fixed_t z) : LegacyActor(x,y,z,MT_BRUISER)
	{
	}
};

[ActorType(MT_KNIGHT)]
ref class HellKnight : LegacyActor
{
public:
	HellKnight(fixed_t x,fixed_t y,fixed_t z) : LegacyActor(x,y,z,MT_KNIGHT)
	{
		Species = (int)MT_BRUISER;
	}
};
