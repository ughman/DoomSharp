#include "p_mobj.hpp"

[ActorType(MT_PLAYER)]
ref class Marine : Actor
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

[ActorType(MT_POSSESSED)]
[DoomedNum(3004)]
ref class Zombieman : Actor
{
public:
	Zombieman()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 20;
		Speed = Fixed(8);
		PainChance = 200;
		SeeSoundNum = sfx_posit1;
		ActiveSoundNum = sfx_posact;
		AttackSoundNum = sfx_pistol;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth1;
		DefineState("Spawn",S_POSS_STND);
		DefineState("See",S_POSS_RUN1);
		DefineState("Missile",S_POSS_ATK1);
		DefineState("Pain",S_POSS_PAIN);
		DefineState("Death",S_POSS_DIE1);
		DefineState("XDeath",S_POSS_XDIE1);
		DefineState("Raise",S_POSS_RAISE1);
	}
};

[ActorType(MT_SHOTGUY)]
[DoomedNum(9)]
ref class Shotgunner : Actor
{
public:
	Shotgunner()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 30;
		Speed = Fixed(8);
		PainChance = 170;
		SeeSoundNum = sfx_posit2;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth2;
		DefineState("Spawn",S_SPOS_STND);
		DefineState("See",S_SPOS_RUN1);
		DefineState("Missile",S_SPOS_ATK1);
		DefineState("Pain",S_SPOS_PAIN);
		DefineState("Death",S_SPOS_DIE1);
		DefineState("XDeath",S_SPOS_XDIE1);
		DefineState("Raise",S_SPOS_RAISE1);
	}
};

[ActorType(MT_VILE)]
[DoomedNum(64)]
ref class Archvile : Actor
{
public:
	Archvile()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 700;
		Speed = Fixed(15);
		Mass = 500;
		PainChance = 10;
		SeeSoundNum = sfx_vilsit;
		ActiveSoundNum = sfx_vilact;
		PainSoundNum = sfx_vipain;
		DeathSoundNum = sfx_vildth;
		DefineState("Spawn",S_VILE_STND);
		DefineState("See",S_VILE_RUN1);
		DefineState("Missile",S_VILE_ATK1);
		DefineState("Pain",S_VILE_PAIN);
		DefineState("Death",S_VILE_DIE1);
	}
};

[ActorType(MT_FIRE)]
ref class Fire : Actor
{
public:
	Fire()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_FIRE1);
	}
};

[ActorType(MT_UNDEAD)]
[DoomedNum(66)]
ref class Revenant : Actor
{
public:
	Revenant()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 300;
		Speed = Fixed(10);
		Mass = 500;
		PainChance = 100;
		SeeSoundNum = sfx_skesit;
		ActiveSoundNum = sfx_skeact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_skedth;
		DefineState("Spawn",S_SKEL_STND);
		DefineState("See",S_SKEL_RUN1);
		DefineState("Melee",S_SKEL_FIST1);
		DefineState("Missile",S_SKEL_MISS1);
		DefineState("Pain",S_SKEL_PAIN);
		DefineState("Death",S_SKEL_DIE1);
		DefineState("Raise",S_SKEL_RAISE1);
	}
};

[ActorType(MT_TRACER)]
ref class RevenantShot : Actor
{
public:
	RevenantShot()
	{
		Radius = Fixed::FromInt(11);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 10;
		SeeSoundNum = sfx_skeatk;
		DeathSoundNum = sfx_barexp;
		DefineState("Spawn",S_TRACER);
		DefineState("Death",S_TRACEEXP1);
	}
};

[ActorType(MT_SMOKE)]
ref class Smoke : Actor
{
public:
	Smoke()
	{
		NoBlockmap = true;
		NoGravity = true;
		DefineState("Spawn",S_SMOKE1);
	}
};

[ActorType(MT_FATSO)]
[DoomedNum(67)]
ref class Mancubus : Actor
{
public:
	Mancubus()
	{
		Radius = Fixed::FromInt(48);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 600;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 80;
		SeeSoundNum = sfx_mansit;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_mnpain;
		DeathSoundNum = sfx_mandth;
		DefineState("Spawn",S_FATT_STND);
		DefineState("See",S_FATT_RUN1);
		DefineState("Missile",S_FATT_ATK1);
		DefineState("Pain",S_FATT_PAIN);
		DefineState("Death",S_FATT_DIE1);
		DefineState("Raise",S_FATT_RAISE1);
	}
};

[ActorType(MT_FATSHOT)]
ref class MancubusShot : Actor
{
public:
	MancubusShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(20);
		Damage = 8;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_FATSHOT1);
		DefineState("Death",S_FATSHOTX1);
	}
};

[ActorType(MT_CHAINGUY)]
[DoomedNum(65)]
ref class Chaingunner : Actor
{
public:
	Chaingunner()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 70;
		Speed = Fixed(8);
		PainChance = 170;
		SeeSoundNum = sfx_posit2;
		ActiveSoundNum = sfx_posact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_podth2;
		DefineState("Spawn",S_CPOS_STND);
		DefineState("See",S_CPOS_RUN1);
		DefineState("Missile",S_CPOS_ATK1);
		DefineState("Pain",S_CPOS_PAIN);
		DefineState("Death",S_CPOS_DIE1);
		DefineState("XDeath",S_CPOS_XDIE1);
		DefineState("Raise",S_CPOS_RAISE1);
	}
};

[ActorType(MT_TROOP)]
[DoomedNum(3001)]
ref class Imp : Actor
{
public:
	Imp()
	{
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 60;
		Speed = Fixed(8);
		PainChance = 200;
		SeeSoundNum = sfx_bgsit1;
		ActiveSoundNum = sfx_bgact;
		PainSoundNum = sfx_popain;
		DeathSoundNum = sfx_bgdth1;
		DefineState("Spawn",S_TROO_STND);
		DefineState("See",S_TROO_RUN1);
		DefineState("Melee",S_TROO_ATK1);
		DefineState("Missile",S_TROO_ATK1);
		DefineState("Pain",S_TROO_PAIN);
		DefineState("Death",S_TROO_DIE1);
		DefineState("XDeath",S_TROO_XDIE1);
		DefineState("Raise",S_TROO_RAISE1);
	}
};

[ActorType(MT_SERGEANT)]
[DoomedNum(3002)]
ref class Demon : Actor
{
public:
	Demon()
	{
		Radius = Fixed::FromInt(30);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 150;
		Speed = Fixed(10);
		Mass = 400;
		PainChance = 180;
		SeeSoundNum = sfx_sgtsit;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sgtatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_sgtdth;
		DefineState("Spawn",S_SARG_STND);
		DefineState("See",S_SARG_RUN1);
		DefineState("Melee",S_SARG_ATK1);
		DefineState("Pain",S_SARG_PAIN);
		DefineState("Death",S_SARG_DIE1);
		DefineState("Raise",S_SARG_RAISE1);
	}
};

[ActorType(MT_SHADOWS)]
[DoomedNum(58)]
ref class Spectre : Actor
{
public:
	Spectre()
	{
		Radius = Fixed::FromInt(30);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		Shadow = true;
		CountKill = true;
		Health = 150;
		Speed = Fixed(10);
		Mass = 400;
		PainChance = 180;
		SeeSoundNum = sfx_sgtsit;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sgtatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_sgtdth;
		DefineState("Spawn",S_SARG_STND);
		DefineState("See",S_SARG_RUN1);
		DefineState("Melee",S_SARG_ATK1);
		DefineState("Pain",S_SARG_PAIN);
		DefineState("Death",S_SARG_DIE1);
		DefineState("Raise",S_SARG_RAISE1);
	}
};

[ActorType(MT_HEAD)]
[DoomedNum(3005)]
ref class Cacodemon : Actor
{
public:
	Cacodemon()
	{
		Radius = Fixed::FromInt(31);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Float = true;
		CountKill = true;
		Health = 400;
		Speed = Fixed(8);
		Mass = 400;
		PainChance = 128;
		SeeSoundNum = sfx_cacsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_cacdth;
		DefineState("Spawn",S_HEAD_STND);
		DefineState("See",S_HEAD_RUN1);
		DefineState("Missile",S_HEAD_ATK1);
		DefineState("Pain",S_HEAD_PAIN);
		DefineState("Death",S_HEAD_DIE1);
		DefineState("Raise",S_HEAD_RAISE1);
	}
};

[ActorType(MT_BRUISER)]
[DoomedNum(3003)]
ref class BaronOfHell : Actor
{
public:
	BaronOfHell()
	{
		Radius = Fixed::FromInt(24);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 50;
		SeeSoundNum = sfx_brssit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_brsdth;
		DefineState("Spawn",S_BOSS_STND);
		DefineState("See",S_BOSS_RUN1);
		DefineState("Melee",S_BOSS_ATK1);
		DefineState("Missile",S_BOSS_ATK1);
		DefineState("Pain",S_BOSS_PAIN);
		DefineState("Death",S_BOSS_DIE1);
		DefineState("Raise",S_BOSS_RAISE1);
	}
};

[ActorType(MT_BRUISERSHOT)]
ref class BaronShot : Actor
{
public:
	BaronShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(15);
		Damage = 8;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_BRBALL1);
		DefineState("Death",S_BRBALLX1);
	}
};

[ActorType(MT_KNIGHT)]
[DoomedNum(69)]
ref class HellKnight : Actor
{
public:
	HellKnight()
	{
		Radius = Fixed::FromInt(24);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 500;
		Speed = Fixed(8);
		Mass = 1000;
		PainChance = 50;
		SeeSoundNum = sfx_kntsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_kntdth;
		DefineState("Spawn",S_BOS2_STND);
		DefineState("See",S_BOS2_RUN1);
		DefineState("Melee",S_BOS2_ATK1);
		DefineState("Missile",S_BOS2_ATK1);
		DefineState("Pain",S_BOS2_PAIN);
		DefineState("Death",S_BOS2_DIE1);
		DefineState("Raise",S_BOS2_RAISE1);
		Species = BaronOfHell::typeid;
	}
};

[ActorType(MT_SKULL)]
[DoomedNum(3006)]
ref class LostSoul : Actor
{
public:
	LostSoul()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Float = true;
		Health = 100;
		Speed = Fixed(8);
		Mass = 50;
		Damage = 3;
		PainChance = 256;
		ActiveSoundNum = sfx_dmact;
		AttackSoundNum = sfx_sklatk;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_SKULL_STND);
		DefineState("See",S_SKULL_RUN1);
		DefineState("Missile",S_SKULL_ATK1);
		DefineState("Pain",S_SKULL_PAIN);
		DefineState("Death",S_SKULL_DIE1);
	}
};

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

[ActorType(MT_BABY)]
[DoomedNum(68)]
ref class Arachnotron : Actor
{
public:
	Arachnotron()
	{
		Radius = Fixed::FromInt(64);
		Height = Fixed::FromInt(64);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 500;
		Speed = Fixed(12);
		Mass = 600;
		PainChance = 128;
		SeeSoundNum = sfx_bspsit;
		ActiveSoundNum = sfx_bspact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_bspdth;
		DefineState("Spawn",S_BSPI_STND);
		DefineState("See",S_BSPI_SIGHT);
		DefineState("Missile",S_BSPI_ATK1);
		DefineState("Pain",S_BSPI_PAIN);
		DefineState("Death",S_BSPI_DIE1);
		DefineState("Raise",S_BSPI_RAISE1);
	}
};

[ActorType(MT_CYBORG)]
[DoomedNum(16)]
ref class Cyberdemon : Actor
{
public:
	Cyberdemon()
	{
		Radius = Fixed::FromInt(40);
		Height = Fixed::FromInt(110);
		Solid = true;
		Shootable = true;
		CountKill = true;
		Health = 4000;
		Speed = Fixed(16);
		Mass = 1000;
		PainChance = 20;
		SeeSoundNum = sfx_cybsit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_dmpain;
		DeathSoundNum = sfx_cybdth;
		DefineState("Spawn",S_CYBER_STND);
		DefineState("See",S_CYBER_RUN1);
		DefineState("Missile",S_CYBER_ATK1);
		DefineState("Pain",S_CYBER_PAIN);
		DefineState("Death",S_CYBER_DIE1);
	}
};

[ActorType(MT_PAIN)]
[DoomedNum(71)]
ref class PainElemental : Actor
{
public:
	PainElemental()
	{
		Radius = Fixed::FromInt(31);
		Height = Fixed::FromInt(56);
		Solid = true;
		Shootable = true;
		NoGravity = true;
		Float = true;
		CountKill = true;
		Health = 400;
		Speed = Fixed(8);
		Mass = 400;
		PainChance = 128;
		SeeSoundNum = sfx_pesit;
		ActiveSoundNum = sfx_dmact;
		PainSoundNum = sfx_pepain;
		DeathSoundNum = sfx_pedth;
		DefineState("Spawn",S_PAIN_STND);
		DefineState("See",S_PAIN_RUN1);
		DefineState("Missile",S_PAIN_ATK1);
		DefineState("Pain",S_PAIN_PAIN);
		DefineState("Death",S_PAIN_DIE1);
		DefineState("Raise",S_PAIN_RAISE1);
	}
};

[ActorType(MT_WOLFSS)]
[DoomedNum(84)]
ref class Nazi : Actor
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

[ActorType(MT_KEEN)]
[DoomedNum(72)]
ref class CommanderKeen : Actor
{
public:
	CommanderKeen()
	{
		Radius = Fixed::FromInt(16);
		Height = Fixed::FromInt(72);
		Solid = true;
		Shootable = true;
		SpawnCeiling = true;
		NoGravity = true;
		CountKill = true;
		Health = 100;
		Mass = 10000000;
		PainChance = 256;
		PainSoundNum = sfx_keenpn;
		DeathSoundNum = sfx_keendt;
		DefineState("Spawn",S_KEENSTND);
		DefineState("Pain",S_KEENPAIN);
		DefineState("Death",S_COMMKEEN);
	}
};

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

[ActorType(MT_TROOPSHOT)]
ref class ImpShot : Actor
{
public:
	ImpShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 3;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_TBALL1);
		DefineState("Death",S_TBALLX1);
	}
};

[ActorType(MT_HEADSHOT)]
ref class CacodemonShot : Actor
{
public:
	CacodemonShot()
	{
		Radius = Fixed::FromInt(6);
		Height = Fixed::FromInt(8);
		NoBlockmap = true;
		NoGravity = true;
		DropOff = true;
		Missile = true;
		Speed = Fixed::FromInt(10);
		Damage = 5;
		SeeSoundNum = sfx_firsht;
		DeathSoundNum = sfx_firxpl;
		DefineState("Spawn",S_RBALL1);
		DefineState("Death",S_RBALLX1);
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

[ActorType(MT_ARACHPLAZ)]
ref class ArachnotronShot : Actor
{
public:
	ArachnotronShot()
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
		DefineState("Spawn",S_ARACH_PLAZ);
		DefineState("Death",S_ARACH_PLEX);
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

[ActorType(MT_MISC0)]
[DoomedNum(2018)]
ref class Armor : Actor
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
ref class MegaArmor : Actor
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
ref class HealthBonus : Actor
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
ref class ArmorBonus : Actor
{
public:
	ArmorBonus()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_BON2);
	}
};

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

[ActorType(MT_MISC10)]
[DoomedNum(2011)]
ref class Stimpack : Actor
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
ref class Medikit : Actor
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
ref class Soulsphere : Actor
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
ref class Invulnerability : Actor
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
ref class Berserk : Actor
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
ref class Invisibility : Actor
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
ref class RadiationSuit : Actor
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
ref class ComputerMap : Actor
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
ref class LightVisor : Actor
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
ref class Megasphere : Actor
{
public:
	Megasphere()
	{
		Special = true;
		CountItem = true;
		DefineState("Spawn",S_MEGA);
	}
};

[ActorType(MT_CLIP)]
[DoomedNum(2007)]
ref class Clip : Actor
{
public:
	Clip()
	{
		Special = true;
		DefineState("Spawn",S_CLIP);
	}
};

[ActorType(MT_MISC17)]
[DoomedNum(2048)]
ref class AmmoBox : Actor
{
public:
	AmmoBox()
	{
		Special = true;
		DefineState("Spawn",S_AMMO);
	}
};

[ActorType(MT_MISC18)]
[DoomedNum(2010)]
ref class RocketAmmo : Actor
{
public:
	RocketAmmo()
	{
		Special = true;
		DefineState("Spawn",S_ROCK);
	}
};

[ActorType(MT_MISC19)]
[DoomedNum(2046)]
ref class RocketBox : Actor
{
public:
	RocketBox()
	{
		Special = true;
		DefineState("Spawn",S_BROK);
	}
};

[ActorType(MT_MISC20)]
[DoomedNum(2047)]
ref class Cell : Actor
{
public:
	Cell()
	{
		Special = true;
		DefineState("Spawn",S_CELL);
	}
};

[ActorType(MT_MISC21)]
[DoomedNum(17)]
ref class CellPack : Actor
{
public:
	CellPack()
	{
		Special = true;
		DefineState("Spawn",S_CELP);
	}
};

[ActorType(MT_MISC22)]
[DoomedNum(2008)]
ref class Shells : Actor
{
public:
	Shells()
	{
		Special = true;
		DefineState("Spawn",S_SHEL);
	}
};

[ActorType(MT_MISC23)]
[DoomedNum(2049)]
ref class ShellBox : Actor
{
public:
	ShellBox()
	{
		Special = true;
		DefineState("Spawn",S_SBOX);
	}
};

[ActorType(MT_MISC24)]
[DoomedNum(8)]
ref class Backpack : Actor
{
public:
	Backpack()
	{
		Special = true;
		DefineState("Spawn",S_BPAK);
	}
};

[ActorType(MT_MISC25)]
[DoomedNum(2006)]
ref class BFG9000 : Actor
{
public:
	BFG9000()
	{
		Special = true;
		DefineState("Spawn",S_BFUG);
	}
};

[ActorType(MT_CHAINGUN)]
[DoomedNum(2002)]
ref class Chaingun : Actor
{
public:
	Chaingun()
	{
		Special = true;
		DefineState("Spawn",S_MGUN);
	}
};

[ActorType(MT_MISC26)]
[DoomedNum(2005)]
ref class Chainsaw : Actor
{
public:
	Chainsaw()
	{
		Special = true;
		DefineState("Spawn",S_CSAW);
	}
};

[ActorType(MT_MISC27)]
[DoomedNum(2003)]
ref class RocketLauncher : Actor
{
public:
	RocketLauncher()
	{
		Special = true;
		DefineState("Spawn",S_LAUN);
	}
};

[ActorType(MT_MISC28)]
[DoomedNum(2004)]
ref class PlasmaRifle : Actor
{
public:
	PlasmaRifle()
	{
		Special = true;
		DefineState("Spawn",S_PLAS);
	}
};

[ActorType(MT_SHOTGUN)]
[DoomedNum(2001)]
ref class Shotgun : Actor
{
public:
	Shotgun()
	{
		Special = true;
		DefineState("Spawn",S_SHOT);
	}
};

[ActorType(MT_SUPERSHOTGUN)]
[DoomedNum(82)]
ref class SuperShotgun : Actor
{
public:
	SuperShotgun()
	{
		Special = true;
		DefineState("Spawn",S_SHOT2);
	}
};

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
