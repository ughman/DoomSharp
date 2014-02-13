#include "p_mobj.hpp"

[ActorType(MT_KEEN)]
[DoomedNum(72)]
ref class CommanderKeen : Actor
{
public:
	CommanderKeen()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(72);
		Solid = true;
		Shootable = true;
		SpawnCeiling = true;
		NoGravity = true;
		CountKill = true;
		Health = 100;
		Mass = 10000000;
		PainChance = 256;
		PainSoundNum = sfx_keenpn;
		DeathSoundNum = sfx_keendt;
		DefineState("Spawn",S_KEENSTND);
		DefineState("Pain",S_KEENPAIN);
		DefineState("Death",S_COMMKEEN);
	}
};
