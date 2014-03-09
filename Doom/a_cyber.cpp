#include "p_mobj.hpp"

[ActorType(MT_CYBORG)]
[DoomedNum(16)]
ref class Cyberdemon : DActor
{
public:
	Cyberdemon()
	{
		Radius = Fixed::FromInt(40);
		Height = Fixed::FromInt(110);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 4000;
		Speed = Fixed(16);
		Mass = 1000;
		PainChance = 20;
		SeeSoundNum = sfx_cybsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_cybdth;
		DefineState("Spawn",S_CYBER_STND);
		DefineState("See",S_CYBER_RUN1);
		DefineState("Missile",S_CYBER_ATK1);
		DefineState("Pain",S_CYBER_PAIN);
		DefineState("Death",S_CYBER_DIE1);
	}
};
