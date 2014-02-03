#include "p_mobj.hpp"

[ActorType(MT_PLAYER)]
ref class Marine : LegacyActor
{
public:
	Marine(fixed_t x,fixed_t y,fixed_t z) : LegacyActor(x,y,z,MT_PLAYER)
	{
		Species = nullptr;
	}
};
