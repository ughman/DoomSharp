#ifndef __B_COMPAT__
#define __B_COMPAT__

enum
{
	COMPAT_SOULBOUNCE = 1,
	COMPAT_TELEPORTZ = 2
};

void B_SetCompat(int flags);
int B_CheckCompat(int flag);

#endif
