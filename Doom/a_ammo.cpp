#include "p_mobj.hpp"

[Scriptable]
[ActorType(MT_CLIP)]
[DoomedNum(2007)]
ref class Clip : DActor
{
public:
	Clip()
	{
		Special = true;
		DefineState("Spawn",S_CLIP);
	}
};

[Scriptable]
[ActorType(MT_MISC17)]
[DoomedNum(2048)]
ref class AmmoBox : DActor
{
public:
	AmmoBox()
	{
		Special = true;
		DefineState("Spawn",S_AMMO);
	}
};

[Scriptable]
[ActorType(MT_MISC18)]
[DoomedNum(2010)]
ref class RocketAmmo : DActor
{
public:
	RocketAmmo()
	{
		Special = true;
		DefineState("Spawn",S_ROCK);
	}
};

[Scriptable]
[ActorType(MT_MISC19)]
[DoomedNum(2046)]
ref class RocketBox : DActor
{
public:
	RocketBox()
	{
		Special = true;
		DefineState("Spawn",S_BROK);
	}
};

[Scriptable]
[ActorType(MT_MISC20)]
[DoomedNum(2047)]
ref class Cell : DActor
{
public:
	Cell()
	{
		Special = true;
		DefineState("Spawn",S_CELL);
	}
};

[Scriptable]
[ActorType(MT_MISC21)]
[DoomedNum(17)]
ref class CellPack : DActor
{
public:
	CellPack()
	{
		Special = true;
		DefineState("Spawn",S_CELP);
	}
};

[Scriptable]
[ActorType(MT_MISC22)]
[DoomedNum(2008)]
ref class Shells : DActor
{
public:
	Shells()
	{
		Special = true;
		DefineState("Spawn",S_SHEL);
	}
};

[Scriptable]
[ActorType(MT_MISC23)]
[DoomedNum(2049)]
ref class ShellBox : DActor
{
public:
	ShellBox()
	{
		Special = true;
		DefineState("Spawn",S_SBOX);
	}
};

[Scriptable]
[ActorType(MT_MISC24)]
[DoomedNum(8)]
ref class Backpack : DActor
{
public:
	Backpack()
	{
		Special = true;
		DefineState("Spawn",S_BPAK);
	}
};
