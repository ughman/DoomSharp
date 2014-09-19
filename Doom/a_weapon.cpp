#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_MISC25)]
[DoomedNum(2006)]
ref class BFG9000 : DActor
{
public:
	BFG9000()
	{
		Special = true;
		DefineState("Spawn",S_BFUG);
	}
};

[Scriptable]
[ActorType(MT_CHAINGUN)]
[DoomedNum(2002)]
ref class Chaingun : DActor
{
public:
	Chaingun()
	{
		Special = true;
		DefineState("Spawn",S_MGUN);
	}
};

[Scriptable]
[ActorType(MT_MISC26)]
[DoomedNum(2005)]
ref class Chainsaw : DActor
{
public:
	Chainsaw()
	{
		Special = true;
		DefineState("Spawn",S_CSAW);
	}
};

[Scriptable]
[ActorType(MT_MISC27)]
[DoomedNum(2003)]
ref class RocketLauncher : DActor
{
public:
	RocketLauncher()
	{
		Special = true;
		DefineState("Spawn",S_LAUN);
	}
};

[Scriptable]
[ActorType(MT_MISC28)]
[DoomedNum(2004)]
ref class PlasmaRifle : DActor
{
public:
	PlasmaRifle()
	{
		Special = true;
		DefineState("Spawn",S_PLAS);
	}
};

[Scriptable]
[ActorType(MT_SHOTGUN)]
[DoomedNum(2001)]
ref class Shotgun : DActor
{
public:
	Shotgun()
	{
		Special = true;
		DefineState("Spawn",S_SHOT);
	}
};

[Scriptable]
[ActorType(MT_SUPERSHOTGUN)]
[DoomedNum(82)]
ref class SuperShotgun : DActor
{
public:
	SuperShotgun()
	{
		Special = true;
		DefineState("Spawn",S_SHOT2);
	}
};
