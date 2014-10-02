using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;

extern "C"
{
#include "i_system.h"
#include "i_sound.h"
#include "i_video.h"
#include "m_misc.h"
}

#include <vcclr.h>
#include <cstdlib>
#include <cstdarg>

gcroot<Stopwatch^> stopwatch;

extern "C" void I_Delay(int tics)
{
	Thread::Sleep(tics * 1000 / TICRATE);
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
	return stopwatch->ElapsedMilliseconds / (1000 / TICRATE);
}

extern "C" void I_Init()
{
	I_InitSound();
	stopwatch = Stopwatch::StartNew();
}

extern "C" void I_Quit()
{
	D_QuitNetGame();
	M_SaveDefaults();
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

static void I_Error2(char *error)
{
	throw gcnew ApplicationException(gcnew String(error));
}

extern "C" void I_Error(char *error,...)
{
	char buffer[1024];
	va_list args;
	va_start(args,error);
	vsnprintf(buffer,sizeof(buffer),error,args);
	va_end(args);
	I_Error2(buffer);
}
