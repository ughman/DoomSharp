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
	vissprite_t *prev = NULL;
	if (vissprites.size())
		prev = &vissprites.back();
	vissprites.push_back(vissprite_t());
	if (prev)
		return prev->next = &vissprites.back();
	return &vissprites.back();
}

extern "C" int R_CountVisSprites()
{
	return vissprites.size();
}

extern "C" vissprite_t *R_FirstVisSprite()
{
	return &vissprites.front();
}
extern "C" vissprite_t *R_LastVisSprite()
{
	return &vissprites.back();
}
