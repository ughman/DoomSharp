#include "p_mobj.hpp"

[ActorType(MT_UNDEAD)]
[DoomedNum(66)]
ref class Revenant : DActor
{
public:
	Revenant()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 300;
		Speed = Fixed(10);
		Mass = 500;
		PainChance = 100;
		SeeSoundNum = sfx_skesit;
		ActiveSoundNum = sfx_skeact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_skedth;
		DefineState("Spawn",S_SKEL_STND);
		DefineState("See",S_SKEL_RUN1);
		DefineState("Melee",S_SKEL_FIST1);
		DefineState("Missile",S_SKEL_MISS1);
		DefineState("Pain",S_SKEL_PAIN);
		DefineState("Death",S_SKEL_DIE1);
		DefineState("Raise",S_SKEL_RAISE1);
	}
};

[ActorType(MT_TRACER)]
ref class RevenantShot : DActor
{
public:
	RevenantShot()
	{
		Radius = Fixed::FromInt(11);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 10;
		SeeSoundNum = sfx_skeatk;
		DeathSoundNum = sfx_barexp;
		DefineState("Spawn",S_TRACER);
		DefineState("Death",S_TRACEEXP1);
	}
};

[ActorType(MT_SMOKE)]
ref class Smoke : DActor
{
public:
	Smoke()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_SMOKE1);
	}
};
