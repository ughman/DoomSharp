#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_VILE)]
[DoomedNum(64)]
ref class Archvile : DActor
{
public:
	Archvile()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 700;
		Speed = Fixed(15);
		Mass = 500;
		PainChance = 10;
		SeeSoundNum = sfx_vilsit;
		ActiveSoundNum = sfx_vilact;
		PainSoundNum = sfx_vipain;
		DeathSoundNum = sfx_vildth;
		DefineState("Spawn",S_VILE_STND);
		DefineState("See",S_VILE_RUN1);
		DefineState("Missile",S_VILE_ATK1);
		DefineState("Pain",S_VILE_PAIN);
		DefineState("Death",S_VILE_DIE1);
	}
};

[Scriptable]
[ActorType(MT_FIRE)]
ref class Fire : DActor
{
public:
	Fire()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_FIRE1);
	}
};
