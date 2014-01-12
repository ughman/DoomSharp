using namespace System::Collections::Generic;
using namespace DoomSharp;

extern "C"
{
#include "p_local.h"
#include "s_sound.h"
#include "doomstat.h"
#include "sounds.h"
}

#include <vcclr.h>

extern void P_AddManagedThinker(Thinker^ thinker);
extern gcroot<List<Thinker^>^> thinkers;

ref class Ceiling : Thinker
{
public:
	sector_t *sector;
	CeilingType type;
	bool active;
	bool crush;
	CeilingDirection direction;
	fixed_t speed;
	fixed_t topheight;
	fixed_t bottomheight;

	Ceiling(sector_t *sector,CeilingType type)
	{
		this->sector = sector;
		this->type = type;
		active = true;
		crush = false;
		speed = CEILSPEED;
		topheight = sector->ceilingheight;
		bottomheight = sector->floorheight;
		switch (type)
		{
		case CeilingType::RaiseToHighest:
			topheight = P_FindHighestCeilingSurrounding(sector);
			direction = CeilingDirection::Up;
			break;
		case CeilingType::FastCrushAndRaise:
			speed = CEILSPEED * 2;
		case CeilingType::CrushAndRaise:
		case CeilingType::SilentCrushAndRaise:
			crush = true;
		case CeilingType::LowerAndCrush:
			bottomheight += FRACUNIT * 8;
		case CeilingType::LowerToFloor:
			direction = CeilingDirection::Down;
		}
	}

	virtual bool Tick() override
	{
		if (!active)
			return false;
		if (direction == CeilingDirection::Up)
		{
			result_e res = T_MovePlane(sector,speed,topheight,false,1,1);
			if (leveltime % 8 == 0 && type != CeilingType::SilentCrushAndRaise)
			{
				S_StartSound((mobj_t *)&sector->soundorg,sfx_stnmov);
			}
			if (res == pastdest)
			{
				switch (type)
				{
				case CeilingType::RaiseToHighest:
					sector->specialdata = NULL;
					return true;
				case CeilingType::SilentCrushAndRaise:
					S_StartSound((mobj_t *)&sector->soundorg,sfx_pstop);
				case CeilingType::CrushAndRaise:
				case CeilingType::FastCrushAndRaise:
					direction = CeilingDirection::Down;
					break;
				}
			}
		}
		else if (direction == CeilingDirection::Down)
		{
			result_e res = T_MovePlane(sector,speed,bottomheight,crush,1,-1);
			if (leveltime % 8 == 0 && type != CeilingType::SilentCrushAndRaise)
			{
				S_StartSound((mobj_t *)&sector->soundorg,sfx_stnmov);
			}
			if (res == pastdest)
			{
				switch (type)
				{
				case CeilingType::LowerToFloor:
				case CeilingType::LowerAndCrush:
					sector->specialdata = NULL;
					return true;
				case CeilingType::SilentCrushAndRaise:
					S_StartSound((mobj_t *)&sector->soundorg,sfx_pstop);
				case CeilingType::CrushAndRaise:
					speed = CEILSPEED;
				case CeilingType::FastCrushAndRaise:
					direction = CeilingDirection::Up;
					break;
				}
			}
			else if (res == crushed)
			{
				switch (type)
				{
				case CeilingType::LowerAndCrush:
				case CeilingType::CrushAndRaise:
				case CeilingType::SilentCrushAndRaise:
					speed = CEILSPEED / 8;
					break;
				}
			}
		}
		return false;
	}
};

int EV_DoCeiling2(line_t *line,ceiling_e type)
{
	int sectornum = -1;
	int ceilingcount = 0;
	for each (Thinker ^thinker in (List<Thinker^>^)thinkers)
	{
		if (thinker->GetType() == Ceiling::typeid)
		{
			ceilingcount++;
			Ceiling^ ceiling = (Ceiling^)thinker;
			if (type == crushAndRaise || type == fastCrushAndRaise || type == silentCrushAndRaise)
			{
				if (ceiling->sector->tag == line->tag)
				{
					ceiling->active = true;
				}
			}
		}
	}
	if (ceilingcount >= MAXCEILINGS)
	{
		return false;
	}
	bool result = false;
	sectornum = -1;
	while ((sectornum = P_FindSectorFromLineTag(line,sectornum)) >= 0)
	{
		sector_t *sector = &sectors[sectornum];
		if (sector->specialdata)
			continue;
		result = true;
		sector->specialdata = (void *)1;
		Ceiling^ ceiling = gcnew Ceiling(sector,(CeilingType)type);
		P_AddManagedThinker(ceiling);
	}
	return result;
}

extern "C" int EV_DoCeiling(line_t *line,ceiling_e type)
{
	return EV_DoCeiling2(line,type);
}

extern "C" int EV_CeilingCrushStop(line_t *line)
{
	bool result = false;
	for each (Thinker ^thinker in (List<Thinker^>^)thinkers)
	{
		if (thinker->GetType() == Ceiling::typeid)
		{
			Ceiling^ ceiling = (Ceiling^)thinker;
			if (ceiling->sector->tag == line->tag)
			{
				result = true;
				ceiling->active = false;
			}
		}
	}
	return result;
}
