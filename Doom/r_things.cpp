extern "C"
{
#include "r_defs.h"
#include "r_things.h"
#include "i_system.h"
}

#include <list>

std::list<vissprite_t> vissprites;

extern "C" void R_ClearSprites()
{
	vissprites.clear();
}

extern "C" vissprite_t *R_NewVisSprite()
{
	vissprites.push_back(vissprite_t());
	return &vissprites.back();
}

static bool SortVisSprite(const vissprite_t &left,const vissprite_t &right)
{
	return left.scale < right.scale;
}

extern "C" void R_SortVisSprites()
{
	vissprites.sort(SortVisSprite);
}

extern "C" void R_DrawSprite(vissprite_t* spr);
extern "C" void R_DrawVisSprites()
{
	for (std::list<vissprite_t>::iterator it = vissprites.begin();it != vissprites.end();it++)
	{
		R_DrawSprite(&*it);
	}
}
