#include "p_mobj.hpp"

[ActorType(MT_TROOP)]
[DoomedNum(3001)]
ref class Imp : Actor
{
public:
	Imp()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 60;
		Speed = Fixed(8);
		PainChance = 200;
		SeeSoundNum = sfx_bgsit1;
		ActiveSoundNum = sfx_bgact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_bgdth1;
		DefineState("Spawn",S_TROO_STND);
		DefineState("See",S_TROO_RUN1);
		DefineState("Melee",S_TROO_ATK1);
		DefineState("Missile",S_TROO_ATK1);
		DefineState("Pain",S_TROO_PAIN);
		DefineState("Death",S_TROO_DIE1);
		DefineState("XDeath",S_TROO_XDIE1);
		DefineState("Raise",S_TROO_RAISE1);
	}
};

[ActorType(MT_TROOPSHOT)]
ref class ImpShot : Actor
{
public:
	ImpShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 3;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_TBALL1);
		DefineState("Death",S_TBALLX1);
	}
};
