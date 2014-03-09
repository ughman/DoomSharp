#include "p_mobj.hpp"

[ActorType(MT_BRUISER)]
[DoomedNum(3003)]
ref class BaronOfHell : DActor
{
public:
	BaronOfHell()
	{
		Radius = Fixed::FromInt(24);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 50;
		SeeSoundNum = sfx_brssit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_brsdth;
		DefineState("Spawn",S_BOSS_STND);
		DefineState("See",S_BOSS_RUN1);
		DefineState("Melee",S_BOSS_ATK1);
		DefineState("Missile",S_BOSS_ATK1);
		DefineState("Pain",S_BOSS_PAIN);
		DefineState("Death",S_BOSS_DIE1);
		DefineState("Raise",S_BOSS_RAISE1);
	}
};

[ActorType(MT_BRUISERSHOT)]
ref class BaronShot : DActor
{
public:
	BaronShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(15);
		Damage = 8;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_BRBALL1);
		DefineState("Death",S_BRBALLX1);
	}
};

[ActorType(MT_KNIGHT)]
[DoomedNum(69)]
ref class HellKnight : DActor
{
public:
	HellKnight()
	{
		Radius = Fixed::FromInt(24);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 500;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 50;
		SeeSoundNum = sfx_kntsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_kntdth;
		DefineState("Spawn",S_BOS2_STND);
		DefineState("See",S_BOS2_RUN1);
		DefineState("Melee",S_BOS2_ATK1);
		DefineState("Missile",S_BOS2_ATK1);
		DefineState("Pain",S_BOS2_PAIN);
		DefineState("Death",S_BOS2_DIE1);
		DefineState("Raise",S_BOS2_RAISE1);
		Species = BaronOfHell::typeid;
	}
};
