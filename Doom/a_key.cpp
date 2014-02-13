#include "p_mobj.hpp"

[ActorType(MT_MISC4)]
[DoomedNum(5)]
ref class BlueCard : Actor
{
public:
	BlueCard()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_BKEY);
	}
};

[ActorType(MT_MISC5)]
[DoomedNum(13)]
ref class RedCard : Actor
{
public:
	RedCard()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_RKEY);
	}
};

[ActorType(MT_MISC6)]
[DoomedNum(6)]
ref class YellowCard : Actor
{
public:
	YellowCard()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_YKEY);
	}
};

[ActorType(MT_MISC7)]
[DoomedNum(39)]
ref class YellowSkull : Actor
{
public:
	YellowSkull()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_YSKULL);
	}
};

[ActorType(MT_MISC8)]
[DoomedNum(38)]
ref class RedSkull : Actor
{
public:
	RedSkull()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_RSKULL);
	}
};

[ActorType(MT_MISC9)]
[DoomedNum(40)]
ref class BlueSkull : Actor
{
public:
	BlueSkull()
	{
		Special = true;
		NotDMatch = true;
		DefineState("Spawn",S_BSKULL);
	}
};
