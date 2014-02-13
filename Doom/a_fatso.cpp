#include "p_mobj.hpp"

[ActorType(MT_FATSO)]
[DoomedNum(67)]
ref class Mancubus : Actor
{
public:
	Mancubus()
	{
		Radius = Fixed::FromInt(48);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 600;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 80;
		SeeSoundNum = sfx_mansit;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_mnpain;
		DeathSoundNum = sfx_mandth;
		DefineState("Spawn",S_FATT_STND);
		DefineState("See",S_FATT_RUN1);
		DefineState("Missile",S_FATT_ATK1);
		DefineState("Pain",S_FATT_PAIN);
		DefineState("Death",S_FATT_DIE1);
		DefineState("Raise",S_FATT_RAISE1);
	}
};

[ActorType(MT_FATSHOT)]
ref class MancubusShot : Actor
{
public:
	MancubusShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(20);
		Damage = 8;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_FATSHOT1);
		DefineState("Death",S_FATSHOTX1);
	}
};
