#include "p_mobj.hpp"

[ActorType(MT_SERGEANT)]
[DoomedNum(3002)]
ref class Demon : DActor
{
public:
	Demon()
	{
		Radius = Fixed::FromInt(30);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 150;
		Speed = Fixed(10);
		Mass = 400;
		PainChance = 180;
		SeeSoundNum = sfx_sgtsit;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sgtatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_sgtdth;
		DefineState("Spawn",S_SARG_STND);
		DefineState("See",S_SARG_RUN1);
		DefineState("Melee",S_SARG_ATK1);
		DefineState("Pain",S_SARG_PAIN);
		DefineState("Death",S_SARG_DIE1);
		DefineState("Raise",S_SARG_RAISE1);
	}
};

[ActorType(MT_SHADOWS)]
[DoomedNum(58)]
ref class Spectre : DActor
{
public:
	Spectre()
	{
		Radius = Fixed::FromInt(30);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		Shadow = true;
		CountKill = true;
		Health = 150;
		Speed = Fixed(10);
		Mass = 400;
		PainChance = 180;
		SeeSoundNum = sfx_sgtsit;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sgtatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_sgtdth;
		DefineState("Spawn",S_SARG_STND);
		DefineState("See",S_SARG_RUN1);
		DefineState("Melee",S_SARG_ATK1);
		DefineState("Pain",S_SARG_PAIN);
		DefineState("Death",S_SARG_DIE1);
		DefineState("Raise",S_SARG_RAISE1);
	}
};
