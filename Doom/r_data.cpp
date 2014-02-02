extern "C"
{
#include "m_fixed.h"
#include "r_defs.h"
#include "z_zone.h"
#include "w_wad.h"
}

#include <map>

struct SpriteInfo
{
	fixed_t width;
	fixed_t offset;
	fixed_t topoffset;
};

std::map<int,SpriteInfo> spriteinfo;

SpriteInfo &GetSpriteInfo(int lump)
{
	std::map<int,SpriteInfo>::iterator it = spriteinfo.find(lump);
	if (it == spriteinfo.end())
	{
		patch_t *patch = (patch_t*)W_CacheLumpNum(lump,PU_CACHE);
		SpriteInfo &info = spriteinfo[lump];
		info.width = patch->width << FRACBITS;
		info.offset = patch->leftoffset << FRACBITS;
		info.topoffset = patch->topoffset << FRACBITS;
		return info;
	}
	else
	{
		return it->second;
	}
}

extern "C" fixed_t R_GetSpriteWidth(int lump)
{
	return GetSpriteInfo(lump).width;
}

extern "C" fixed_t R_GetSpriteOffset(int lump)
{
	return GetSpriteInfo(lump).offset;
}

extern "C" fixed_t R_GetSpriteTopOffset(int lump)
{
	return GetSpriteInfo(lump).topoffset;
}
