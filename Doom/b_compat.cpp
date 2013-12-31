using namespace DoomSharp;

extern "C"
{
#include "b_compat.h"
}

#include <vcclr.h>

static gcroot<CompatFlags^> compatflags;

static void B_InitCompat()
{
	if (!compatflags)
		compatflags = gcnew CompatFlags();
}

extern "C" void B_SetCompat(int flags)
{
	B_InitCompat();
	compatflags = *(CompatFlags^)compatflags | (CompatFlags)flags;
}

extern "C" int B_CheckCompat(int flag)
{
	B_InitCompat();
	return !!((int)*(CompatFlags^)compatflags & flag);
}
