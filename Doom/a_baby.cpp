#include "p_mobj.hpp"

[ActorType(MT_BABY)]
[DoomedNum(68)]
ref class Arachnotron : DActor
{
public:
	Arachnotron()
	{
		Radius = Fixed::FromInt(64);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 500;
		Speed = Fixed(12);
		Mass = 600;
		PainChance = 128;
		SeeSoundNum = sfx_bspsit;
		ActiveSoundNum = sfx_bspact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_bspdth;
		DefineState("Spawn",S_BSPI_STND);
		DefineState("See",S_BSPI_SIGHT);
		DefineState("Missile",S_BSPI_ATK1);
		DefineState("Pain",S_BSPI_PAIN);
		DefineState("Death",S_BSPI_DIE1);
		DefineState("Raise",S_BSPI_RAISE1);
	}
};

[ActorType(MT_ARACHPLAZ)]
ref class ArachnotronShot : DActor
{
public:
	ArachnotronShot()
	{
		Radius = Fixed::FromInt(13);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(25);
		Damage = 5;
		SeeSoundNum = sfx_plasma;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_ARACH_PLAZ);
		DefineState("Death",S_ARACH_PLEX);
	}
};
