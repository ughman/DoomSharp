#include "p_mobj.hpp"

[ActorType(MT_MISC29)]
[DoomedNum(85)]
ref class TechLamp : Actor
{
public:
	TechLamp()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TECHLAMP);
	}
};

[ActorType(MT_MISC30)]
[DoomedNum(86)]
ref class TechLamp2 : Actor
{
public:
	TechLamp2()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TECH2LAMP);
	}
};

[ActorType(MT_MISC31)]
[DoomedNum(2028)]
ref class Column : Actor
{
public:
	Column()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_COLU);
	}
};

[ActorType(MT_MISC32)]
[DoomedNum(30)]
ref class TallGreenColumn : Actor
{
public:
	TallGreenColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TALLGRNCOL);
	}
};

[ActorType(MT_MISC33)]
[DoomedNum(31)]
ref class ShortGreenColumn : Actor
{
public:
	ShortGreenColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_SHRTGRNCOL);
	}
};

[ActorType(MT_MISC34)]
[DoomedNum(32)]
ref class TallRedColumn : Actor
{
public:
	TallRedColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TALLREDCOL);
	}
};

[ActorType(MT_MISC35)]
[DoomedNum(33)]
ref class ShortRedColumn : Actor
{
public:
	ShortRedColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_SHRTREDCOL);
	}
};

[ActorType(MT_MISC36)]
[DoomedNum(37)]
ref class SkullColumn : Actor
{
public:
	SkullColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_SKULLCOL);
	}
};

[ActorType(MT_MISC37)]
[DoomedNum(36)]
ref class HeartColumn : Actor
{
public:
	HeartColumn()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_HEARTCOL);
	}
};

[ActorType(MT_MISC38)]
[DoomedNum(41)]
ref class EvilEye : Actor
{
public:
	EvilEye()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_EVILEYE);
	}
};

[ActorType(MT_MISC39)]
[DoomedNum(42)]
ref class FloatingSkulls : Actor
{
public:
	FloatingSkulls()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_FLOATSKULL);
	}
};

[ActorType(MT_MISC40)]
[DoomedNum(43)]
ref class TorchedTree : Actor
{
public:
	TorchedTree()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TORCHTREE);
	}
};

[ActorType(MT_MISC41)]
[DoomedNum(44)]
ref class BlueTorch : Actor
{
public:
	BlueTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_BLUETORCH);
	}
};

[ActorType(MT_MISC42)]
[DoomedNum(45)]
ref class GreenTorch : Actor
{
public:
	GreenTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_GREENTORCH);
	}
};

[ActorType(MT_MISC43)]
[DoomedNum(46)]
ref class RedTorch : Actor
{
public:
	RedTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_REDTORCH);
	}
};

[ActorType(MT_MISC44)]
[DoomedNum(55)]
ref class ShortBlueTorch : Actor
{
public:
	ShortBlueTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_BTORCHSHRT);
	}
};

[ActorType(MT_MISC45)]
[DoomedNum(56)]
ref class ShortGreenTorch : Actor
{
public:
	ShortGreenTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_GTORCHSHRT);
	}
};

[ActorType(MT_MISC46)]
[DoomedNum(57)]
ref class ShortRedTorch : Actor
{
public:
	ShortRedTorch()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_RTORCHSHRT);
	}
};

[ActorType(MT_MISC47)]
[DoomedNum(47)]
ref class Stalagtite : Actor
{
public:
	Stalagtite()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_STALAGTITE);
	}
};

[ActorType(MT_MISC48)]
[DoomedNum(48)]
ref class TechPillar : Actor
{
public:
	TechPillar()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_TECHPILLAR);
	}
};

[ActorType(MT_MISC49)]
[DoomedNum(34)]
ref class Candle : Actor
{
public:
	Candle()
	{
		DefineState("Spawn",S_CANDLESTIK);
	}
};

[ActorType(MT_MISC50)]
[DoomedNum(35)]
ref class Candelabra : Actor
{
public:
	Candelabra()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_CANDELABRA);
	}
};

[ActorType(MT_MISC51)]
[DoomedNum(49)]
ref class Actor101 : Actor
{
public:
	Actor101()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(68);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_BLOODYTWITCH);
	}
};

[ActorType(MT_MISC52)]
[DoomedNum(50)]
ref class Actor102 : Actor
{
public:
	Actor102()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(84);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT2);
	}
};

[ActorType(MT_MISC53)]
[DoomedNum(51)]
ref class Actor103 : Actor
{
public:
	Actor103()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(84);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT3);
	}
};

[ActorType(MT_MISC54)]
[DoomedNum(52)]
ref class Actor104 : Actor
{
public:
	Actor104()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(68);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT4);
	}
};

[ActorType(MT_MISC55)]
[DoomedNum(53)]
ref class Actor105 : Actor
{
public:
	Actor105()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(52);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT5);
	}
};

[ActorType(MT_MISC56)]
[DoomedNum(59)]
ref class Actor106 : Actor
{
public:
	Actor106()
	{
		Height = Fixed::FromInt(84);
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT2);
	}
};

[ActorType(MT_MISC57)]
[DoomedNum(60)]
ref class Actor107 : Actor
{
public:
	Actor107()
	{
		Height = Fixed::FromInt(68);
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT4);
	}
};

[ActorType(MT_MISC58)]
[DoomedNum(61)]
ref class Actor108 : Actor
{
public:
	Actor108()
	{
		Height = Fixed::FromInt(52);
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT3);
	}
};

[ActorType(MT_MISC59)]
[DoomedNum(62)]
ref class Actor109 : Actor
{
public:
	Actor109()
	{
		Height = Fixed::FromInt(52);
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_MEAT5);
	}
};

[ActorType(MT_MISC60)]
[DoomedNum(63)]
ref class Actor110 : Actor
{
public:
	Actor110()
	{
		Height = Fixed::FromInt(68);
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_BLOODYTWITCH);
	}
};

[ActorType(MT_MISC61)]
[DoomedNum(22)]
ref class DeadCacodemon : Actor
{
public:
	DeadCacodemon()
	{
		DefineState("Spawn",S_HEAD_DIE6);
	}
};

[ActorType(MT_MISC62)]
[DoomedNum(15)]
ref class DeadMarine : Actor
{
public:
	DeadMarine()
	{
		DefineState("Spawn",S_PLAY_DIE7);
	}
};

[ActorType(MT_MISC63)]
[DoomedNum(18)]
ref class DeadZombieman : Actor
{
public:
	DeadZombieman()
	{
		DefineState("Spawn",S_POSS_DIE5);
	}
};

[ActorType(MT_MISC64)]
[DoomedNum(21)]
ref class DeadDemon : Actor
{
public:
	DeadDemon()
	{
		DefineState("Spawn",S_SARG_DIE6);
	}
};

[ActorType(MT_MISC65)]
[DoomedNum(23)]
ref class DeadLostSoul : Actor
{
public:
	DeadLostSoul()
	{
		DefineState("Spawn",S_SKULL_DIE6);
	}
};

[ActorType(MT_MISC66)]
[DoomedNum(20)]
ref class DeadImp : Actor
{
public:
	DeadImp()
	{
		DefineState("Spawn",S_TROO_DIE5);
	}
};

[ActorType(MT_MISC67)]
[DoomedNum(19)]
ref class DeadShotgunner : Actor
{
public:
	DeadShotgunner()
	{
		DefineState("Spawn",S_SPOS_DIE5);
	}
};

[ActorType(MT_MISC68)]
[DoomedNum(10)]
ref class MarineGib : Actor
{
public:
	MarineGib()
	{
		DefineState("Spawn",S_PLAY_XDIE9);
	}
};

[ActorType(MT_MISC69)]
[DoomedNum(12)]
ref class MarineGib2 : Actor
{
public:
	MarineGib2()
	{
		DefineState("Spawn",S_PLAY_XDIE9);
	}
};

[ActorType(MT_MISC70)]
[DoomedNum(28)]
ref class HeadsOnAStick : Actor
{
public:
	HeadsOnAStick()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_HEADSONSTICK);
	}
};

[ActorType(MT_MISC71)]
[DoomedNum(24)]
ref class Actor121 : Actor
{
public:
	Actor121()
	{
		DefineState("Spawn",S_GIBS);
	}
};

[ActorType(MT_MISC72)]
[DoomedNum(27)]
ref class HeadOnAStick : Actor
{
public:
	HeadOnAStick()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_HEADONASTICK);
	}
};

[ActorType(MT_MISC73)]
[DoomedNum(29)]
ref class HeadCandles : Actor
{
public:
	HeadCandles()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_HEADCANDLES);
	}
};

[ActorType(MT_MISC74)]
[DoomedNum(25)]
ref class DeadStick : Actor
{
public:
	DeadStick()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_DEADSTICK);
	}
};

[ActorType(MT_MISC75)]
[DoomedNum(26)]
ref class LiveStick : Actor
{
public:
	LiveStick()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_LIVESTICK);
	}
};

[ActorType(MT_MISC76)]
[DoomedNum(54)]
ref class BigTree : Actor
{
public:
	BigTree()
	{
		Radius = Fixed::FromInt(32);
		Solid = true;
		DefineState("Spawn",S_BIGTREE);
	}
};

[ActorType(MT_MISC77)]
[DoomedNum(70)]
ref class BurningBarrel : Actor
{
public:
	BurningBarrel()
	{
		Radius = Fixed::FromInt(16);
		Solid = true;
		DefineState("Spawn",S_BBAR1);
	}
};

[ActorType(MT_MISC78)]
[DoomedNum(73)]
ref class Actor128 : Actor
{
public:
	Actor128()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(88);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGNOGUTS);
	}
};

[ActorType(MT_MISC79)]
[DoomedNum(74)]
ref class Actor129 : Actor
{
public:
	Actor129()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(88);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGBNOBRAIN);
	}
};

[ActorType(MT_MISC80)]
[DoomedNum(75)]
ref class Actor130 : Actor
{
public:
	Actor130()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(64);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGTLOOKDN);
	}
};

[ActorType(MT_MISC81)]
[DoomedNum(76)]
ref class Actor131 : Actor
{
public:
	Actor131()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(64);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGTSKULL);
	}
};

[ActorType(MT_MISC82)]
[DoomedNum(77)]
ref class Actor132 : Actor
{
public:
	Actor132()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(64);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGTLOOKUP);
	}
};

[ActorType(MT_MISC83)]
[DoomedNum(78)]
ref class Actor133 : Actor
{
public:
	Actor133()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(64);
		Solid = true;
		SpawnCeiling = true;
		NoGravity = true;
		DefineState("Spawn",S_HANGTNOBRAIN);
	}
};

[ActorType(MT_MISC84)]
[DoomedNum(79)]
ref class Actor134 : Actor
{
public:
	Actor134()
	{
		NoBlockmap = true;
		DefineState("Spawn",S_COLONGIBS);
	}
};

[ActorType(MT_MISC85)]
[DoomedNum(80)]
ref class Actor135 : Actor
{
public:
	Actor135()
	{
		NoBlockmap = true;
		DefineState("Spawn",S_SMALLPOOL);
	}
};

[ActorType(MT_MISC86)]
[DoomedNum(81)]
ref class Actor136 : Actor
{
public:
	Actor136()
	{
		NoBlockmap = true;
		DefineState("Spawn",S_BRAINSTEM);
	}
};
