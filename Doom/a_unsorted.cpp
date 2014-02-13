#include "p_mobj.hpp"

[ActorType(MT_BARREL)]
[DoomedNum(2035)]
ref class Barrel : Actor
{
public:
	Barrel()
	{
		Radius = Fixed::FromInt(10);
		Height = Fixed::FromInt(42);
		Solid = true;
		Shootable = true;
		NoBlood = true;
		Health = 20;
		DeathSoundNum = sfx_barexp;
		DefineState("Spawn",S_BAR1);
		DefineState("Death",S_BEXP);
	}
};

[ActorType(MT_ROCKET)]
ref class Rocket : Actor
{
public:
	Rocket()
	{
		Radius = Fixed::FromInt(11);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(20);
		Damage = 20;
		SeeSoundNum = sfx_rlaunc;
		DeathSoundNum = sfx_barexp;
		DefineState("Spawn",S_ROCKET);
		DefineState("Death",S_EXPLODE1);
	}
};

[ActorType(MT_PLASMA)]
ref class PlasmaBall : Actor
{
public:
	PlasmaBall()
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
		DefineState("Spawn",S_PLASBALL);
		DefineState("Death",S_PLASEXP);
	}
};

[ActorType(MT_BFG)]
ref class BFGBall : Actor
{
public:
	BFGBall()
	{
		Radius = Fixed::FromInt(13);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(25);
		Damage = 100;
		DeathSoundNum = sfx_rxplod;
		DefineState("Spawn",S_BFGSHOT);
		DefineState("Death",S_BFGLAND);
	}
};

[ActorType(MT_PUFF)]
ref class Puff : Actor
{
public:
	Puff()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_PUFF1);
	}
};

[ActorType(MT_BLOOD)]
ref class Blood : Actor
{
public:
	Blood()
	{
		NoBlockmap = true;
		DefineState("Spawn",S_BLOOD1);
	}
};

[ActorType(MT_TFOG)]
ref class TeleportFog : Actor
{
public:
	TeleportFog()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_TFOG);
	}
};

[ActorType(MT_IFOG)]
ref class ItemFog : Actor
{
public:
	ItemFog()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_IFOG);
	}
};

[ActorType(MT_TELEPORTMAN)]
[DoomedNum(14)]
ref class TeleportDestination : Actor
{
public:
	TeleportDestination()
	{
		NoSector = true;
		NoBlockmap = true;
	}
};

[ActorType(MT_EXTRABFG)]
ref class BFGExtra : Actor
{
public:
	BFGExtra()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_BFGEXP);
	}
};
