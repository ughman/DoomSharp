extern "C"
{
#include "r_plane.h"
#include "doomstat.h"
}

#include <list>
#include <map>

std::list<visplane_t> visplanes;
std::map<int,int> flattranslation;

extern "C" void R_ClearPlanes()
{
	visplanes.clear();
	R_ClearPlanes2();
}

extern "C" visplane_t *R_FindPlane(fixed_t height,int picnum,int lightlevel)
{
	if (picnum == skyflatnum)
	{
		height = 0;
		lightlevel = 0;
	}
	for (std::list<visplane_t>::iterator it = visplanes.begin();it != visplanes.end();it++)
	{
		if (it->height == height && it->picnum == picnum && it->lightlevel == lightlevel)
		{
			return &*it;
		}
	}
	visplane_t plane;
	memset(&plane,0,sizeof(plane));
	plane.height = height;
	plane.picnum = picnum;
	plane.lightlevel = lightlevel;
	plane.minx = SCREENWIDTH;
	plane.maxx = -1;
	memset(plane.top,0xFF,sizeof(plane.top));
	visplanes.push_back(plane);
	return &visplanes.back();
}

extern "C" visplane_t *R_AddPlane(visplane_t *base)
{
	visplanes.push_back(*base);
	return &visplanes.back();
}

extern "C" void R_DrawPlanes()
{
	for (std::list<visplane_t>::iterator it = visplanes.begin();it != visplanes.end();it++)
	{
		R_DrawPlane(&*it);
	}
}

extern "C" int R_GetFlatTranslation(int flat)
{
	std::map<int,int>::iterator it = flattranslation.find(flat);
	if (it == flattranslation.end())
	{
		return flattranslation[flat] = flat;
	}
	return it->second;
}

extern "C" void R_SetFlatTranslation(int flat,int translation)
{
	flattranslation[flat] = translation;
}
