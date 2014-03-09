#include "p_mobj.hpp"

[ActorType(MT_MISC0)]
[DoomedNum(2018)]
ref class Armor : DActor
{
public:
	Armor()
	{
		Special = true;
		DefineState("Spawn",S_ARM1);
	}
};

[ActorType(MT_MISC1)]
[DoomedNum(2019)]
ref class MegaArmor : DActor
{
public:
	MegaArmor()
	{
		Special = true;
		DefineState("Spawn",S_ARM2);
	}
};

[ActorType(MT_MISC2)]
[DoomedNum(2014)]
ref class HealthBonus : DActor
{
public:
	HealthBonus()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_BON1);
	}
};

[ActorType(MT_MISC3)]
[DoomedNum(2015)]
ref class ArmorBonus : DActor
{
public:
	ArmorBonus()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_BON2);
	}
};

[ActorType(MT_MISC10)]
[DoomedNum(2011)]
ref class Stimpack : DActor
{
public:
	Stimpack()
	{
		Special = true;
		DefineState("Spawn",S_STIM);
	}
};

[ActorType(MT_MISC11)]
[DoomedNum(2012)]
ref class Medikit : DActor
{
public:
	Medikit()
	{
		Special = true;
		DefineState("Spawn",S_MEDI);
	}
};

[ActorType(MT_MISC12)]
[DoomedNum(2013)]
ref class Soulsphere : DActor
{
public:
	Soulsphere()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_SOUL);
	}
};

[ActorType(MT_INV)]
[DoomedNum(2022)]
ref class Invulnerability : DActor
{
public:
	Invulnerability()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_PINV);
	}
};

[ActorType(MT_MISC13)]
[DoomedNum(2023)]
ref class Berserk : DActor
{
public:
	Berserk()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_PSTR);
	}
};

[ActorType(MT_INS)]
[DoomedNum(2024)]
ref class Invisibility : DActor
{
public:
	Invisibility()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_PINS);
	}
};

[ActorType(MT_MISC14)]
[DoomedNum(2025)]
ref class RadiationSuit : DActor
{
public:
	RadiationSuit()
	{
		Special = true;
		DefineState("Spawn",S_SUIT);
	}
};

[ActorType(MT_MISC15)]
[DoomedNum(2026)]
ref class ComputerMap : DActor
{
public:
	ComputerMap()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_PMAP);
	}
};

[ActorType(MT_MISC16)]
[DoomedNum(2045)]
ref class LightVisor : DActor
{
public:
	LightVisor()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_PVIS);
	}
};

[ActorType(MT_MEGA)]
[DoomedNum(83)]
ref class Megasphere : DActor
{
public:
	Megasphere()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_MEGA);
	}
};
