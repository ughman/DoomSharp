#include "p_mobj.hpp"

[ActorType(MT_PAIN)]
[DoomedNum(71)]
ref class PainElemental : DActor
{
public:
	PainElemental()
	{
		Radius = Fixed::FromInt(31);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Float = true;
		CountKill = true;
		Health = 400;
		Speed = Fixed(8);
		Mass = 400;
		PainChance = 128;
		SeeSoundNum = sfx_pesit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_pepain;
		DeathSoundNum = sfx_pedth;
		DefineState("Spawn",S_PAIN_STND);
		DefineState("See",S_PAIN_RUN1);
		DefineState("Missile",S_PAIN_ATK1);
		DefineState("Pain",S_PAIN_PAIN);
		DefineState("Death",S_PAIN_DIE1);
		DefineState("Raise",S_PAIN_RAISE1);
	}
};
