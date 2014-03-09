#include "p_mobj.hpp"

[ActorType(MT_WOLFSS)]
[DoomedNum(84)]
ref class Nazi : DActor
{
public:
	Nazi()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 50;
		Speed = Fixed(8);
		PainChance = 170;
		SeeSoundNum = sfx_sssit;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_ssdth;
		DefineState("Spawn",S_SSWV_STND);
		DefineState("See",S_SSWV_RUN1);
		DefineState("Missile",S_SSWV_ATK1);
		DefineState("Pain",S_SSWV_PAIN);
		DefineState("Death",S_SSWV_DIE1);
		DefineState("XDeath",S_SSWV_XDIE1);
		DefineState("Raise",S_SSWV_RAISE1);
	}
};
