using namespace DoomSharp;

#include "p_setup.hpp"
#include "p_mobj.hpp"

extern "C" int P_InitSpecialLine2(line_t *linedef)
{
	LinedefSpecial^ special = LinedefSpecial::GetSpecial(linedef->special);
	if (!special)
		return false;
	if ((special->ActivationType & LinedefActivationType::Automatic) != LinedefActivationType::Automatic)
		return false;
	special->Activate(nullptr,DLinedef::FromPtr(linedef),false);
	return true;
}

extern "C" int P_UseSpecialLine2(mobj_t *mobj,line_t *linedef,int side)
{
	LinedefSpecial^ special = LinedefSpecial::GetSpecial(linedef->special);
	if (!special)
		return false;
	if (mobj->player && (special->ActivationType & LinedefActivationType::Use) != LinedefActivationType::Use)
		return false;
	if (!mobj->player && (special->ActivationType & LinedefActivationType::MonsterUse) != LinedefActivationType::MonsterUse)
		return false;
	if (special->Activate(DActor::FromPtr(mobj),DLinedef::FromPtr(linedef),side))
		P_ChangeSwitchTexture(linedef,special->Repeatable);
	return true;
}

extern "C" int P_CrossSpecialLine2(mobj_t *mobj,line_t *linedef,int side)
{
	LinedefSpecial^ special = LinedefSpecial::GetSpecial(linedef->special);
	if (!special)
		return false;
	if (mobj->player && (special->ActivationType & LinedefActivationType::Cross) != LinedefActivationType::Cross)
		return false;
	if (!mobj->player && (special->ActivationType & LinedefActivationType::MonsterCross) != LinedefActivationType::MonsterCross)
		return false;
	if (special->Activate(DActor::FromPtr(mobj),DLinedef::FromPtr(linedef),side) && !special->Repeatable)
		linedef->special = 0;
	return true;
}

extern "C" int P_ShootSpecialLine2(mobj_t *mobj,line_t *linedef,int side)
{
	LinedefSpecial^ special = LinedefSpecial::GetSpecial(linedef->special);
	if (!special)
		return false;
	if (mobj->player && (special->ActivationType & LinedefActivationType::Shoot) != LinedefActivationType::Shoot)
		return false;
	if (!mobj->player && (special->ActivationType & LinedefActivationType::MonsterShoot) != LinedefActivationType::MonsterShoot)
		return false;
	if (special->Activate(DActor::FromPtr(mobj),DLinedef::FromPtr(linedef),side))
		P_ChangeSwitchTexture(linedef,special->Repeatable);
	return true;
}
