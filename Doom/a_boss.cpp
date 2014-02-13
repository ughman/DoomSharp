#include "p_mobj.hpp"

[ActorType(MT_BOSSBRAIN)]
[DoomedNum(88)]
ref class BossBrain : Actor
{
public:
	BossBrain()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		Shootable = true;
		Health = 250;
		Mass = 10000000;
		PainChance = 255;
		PainSoundNum = sfx_bospn;
		DeathSoundNum = sfx_bosdth;
		DefineState("Spawn",S_BRAIN);
		DefineState("Pain",S_BRAIN_PAIN);
		DefineState("Death",S_BRAIN_DIE1);
	}
};

[ActorType(MT_BOSSSPIT)]
[DoomedNum(89)]
ref class BossEye : Actor
{
public:
	BossEye()
	{
		Height = Fixed::FromInt(32);
		NoSector = true;
		NoBlockmap = true;
		DefineState("Spawn",S_BRAINEYE);
		DefineState("See",S_BRAINEYESEE);
	}
};

[ActorType(MT_BOSSTARGET)]
[DoomedNum(87)]
ref class BossTarget : Actor
{
public:
	BossTarget()
	{
		Height = Fixed::FromInt(32);
		NoSector = true;
		NoBlockmap = true;
	}
};

[ActorType(MT_SPAWNSHOT)]
ref class BossShot : Actor
{
public:
	BossShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(32);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		NoClip = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 3;
		SeeSoundNum = sfx_bospit;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_SPAWN1);
	}
};

[ActorType(MT_SPAWNFIRE)]
ref class SpawnFire : Actor
{
public:
	SpawnFire()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_SPAWNFIRE1);
	}
};
