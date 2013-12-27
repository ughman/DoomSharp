extern "C"
{
#include "i_system.h"
#include "i_sound.h"
#include "i_video.h"
#include "m_misc.h"
}

#include <cstdlib>
#include <cstdarg>

extern "C" void I_Tactile(int on,int off,int total)
{
}

extern "C" ticcmd_t *I_BaseTiccmd()
{
	static ticcmd_t baseticcmd;
	return &baseticcmd;
}

extern "C" byte *I_ZoneBase(int *size)
{
	static byte zonedata[16 * 1024 * 1024];
	*size = sizeof(zonedata);
	return zonedata;
}

extern "C" int I_GetTime()
{
	// TODO
	return 0;
}

extern "C" void I_Init()
{
	I_InitSound();
}

extern "C" void I_Quit()
{
	D_QuitNetGame();
	I_ShutdownSound();
	I_ShutdownMusic();
	M_SaveDefaults();
	I_ShutdownGraphics();
	exit(0);
}

extern "C" void I_WaitVBL(int count)
{
	// TODO
}

extern "C" byte *I_AllocLow(int length)
{
	return (byte *)calloc(1,length);
}

extern "C" void I_Error(char *error,...)
{
	char buffer[1024];
	va_list args;
	va_start(args,error);
	vsnprintf(buffer,sizeof(buffer),error,args);
	va_end(args);
	abort();
}
