#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_HEAD)]
[DoomedNum(3005)]
ref class Cacodemon : DActor
{
public:
	Cacodemon()
	{
		Radius = Fixed::FromInt(31);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Floats = true;
		CountKill = true;
		Health = 400;
		Speed = Fixed(8);
		Mass = 400;
		PainChance = 128;
		SeeSoundNum = sfx_cacsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_cacdth;
		DefineState("Spawn",S_HEAD_STND);
		DefineState("See",S_HEAD_RUN1);
		DefineState("Missile",S_HEAD_ATK1);
		DefineState("Pain",S_HEAD_PAIN);
		DefineState("Death",S_HEAD_DIE1);
		DefineState("Raise",S_HEAD_RAISE1);
	}
};

[Scriptable]
[ActorType(MT_HEADSHOT)]
ref class CacodemonShot : DActor
{
public:
	CacodemonShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 5;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_RBALL1);
		DefineState("Death",S_RBALLX1);
	}
};
