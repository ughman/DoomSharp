#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_PLAYER)]
ref class Marine : DActor
{
public:
	Marine()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		DropOff = true;
		Pickup = true;
		NotDMatch = true;
		Health = 100;
		ReactionTime = 0;
		PainChance = 255;
		PainSoundNum = sfx_plpain;
		DeathSoundNum = sfx_pldeth;
		DefineState("Spawn",S_PLAY);
		DefineState("See",S_PLAY_RUN1);
		DefineState("Missile",S_PLAY_ATK1);
		DefineState("Pain",S_PLAY_PAIN);
		DefineState("Death",S_PLAY_DIE1);
		DefineState("XDeath",S_PLAY_XDIE1);
		Species = nullptr;
	}
};
