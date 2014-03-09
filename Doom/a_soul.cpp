#include "p_mobj.hpp"

[ActorType(MT_SKULL)]
[DoomedNum(3006)]
ref class LostSoul : DActor
{
public:
	LostSoul()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Float = true;
		Health = 100;
		Speed = Fixed(8);
		Mass = 50;
		Damage = 3;
		PainChance = 256;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sklatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_SKULL_STND);
		DefineState("See",S_SKULL_RUN1);
		DefineState("Missile",S_SKULL_ATK1);
		DefineState("Pain",S_SKULL_PAIN);
		DefineState("Death",S_SKULL_DIE1);
	}
};
