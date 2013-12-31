#ifndef __B_COMPAT__
#define __B_COMPAT__

enum
{
	COMPAT_SOULBOUNCE,
	COMPAT_TELEPORTZ
};

void B_SetCompat(int flags);
int B_CheckCompat(int flag);

#endif
