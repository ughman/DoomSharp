#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_POSSESSED)]
[DoomedNum(3004)]
ref class Zombieman : DActor
{
public:
	Zombieman()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 20;
		Speed = Fixed(8);
		PainChance = 200;
		SeeSoundNum = sfx_posit1;
		ActiveSoundNum = sfx_posact;
		AttackSoundNum = sfx_pistol;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth1;
		DefineState("Spawn",S_POSS_STND);
		DefineState("See",S_POSS_RUN1);
		DefineState("Missile",S_POSS_ATK1);
		DefineState("Pain",S_POSS_PAIN);
		DefineState("Death",S_POSS_DIE1);
		DefineState("XDeath",S_POSS_XDIE1);
		DefineState("Raise",S_POSS_RAISE1);
	}
};

[Scriptable]
[ActorType(MT_SHOTGUY)]
[DoomedNum(9)]
ref class Shotgunner : DActor
{
public:
	Shotgunner()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 30;
		Speed = Fixed(8);
		PainChance = 170;
		SeeSoundNum = sfx_posit2;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth2;
		DefineState("Spawn",S_SPOS_STND);
		DefineState("See",S_SPOS_RUN1);
		DefineState("Missile",S_SPOS_ATK1);
		DefineState("Pain",S_SPOS_PAIN);
		DefineState("Death",S_SPOS_DIE1);
		DefineState("XDeath",S_SPOS_XDIE1);
		DefineState("Raise",S_SPOS_RAISE1);
	}
};

[Scriptable]
[ActorType(MT_CHAINGUY)]
[DoomedNum(65)]
ref class Chaingunner : DActor
{
public:
	Chaingunner()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 70;
		Speed = Fixed(8);
		PainChance = 170;
		SeeSoundNum = sfx_posit2;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth2;
		DefineState("Spawn",S_CPOS_STND);
		DefineState("See",S_CPOS_RUN1);
		DefineState("Missile",S_CPOS_ATK1);
		DefineState("Pain",S_CPOS_PAIN);
		DefineState("Death",S_CPOS_DIE1);
		DefineState("XDeath",S_CPOS_XDIE1);
		DefineState("Raise",S_CPOS_RAISE1);
	}
};
