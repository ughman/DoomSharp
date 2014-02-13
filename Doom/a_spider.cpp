#include "p_mobj.hpp"

[ActorType(MT_SPIDER)]
[DoomedNum(7)]
ref class SpiderMastermind : Actor
{
public:
	SpiderMastermind()
	{
		Radius = Fixed::FromInt(128);
		Height = Fixed::FromInt(100);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 3000;
		Speed = Fixed(12);
		Mass = 1000;
		PainChance = 40;
		SeeSoundNum = sfx_spisit;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_shotgn;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_spidth;
		DefineState("Spawn",S_SPID_STND);
		DefineState("See",S_SPID_RUN1);
		DefineState("Missile",S_SPID_ATK1);
		DefineState("Pain",S_SPID_PAIN);
		DefineState("Death",S_SPID_DIE1);
	}
};
