extern "C"
{
#include "i_video.h"
#include "v_video.h"
}

extern "C" void I_ShutdownGraphics()
{
	// TODO
}

extern "C" void I_StartFrame()
{
	// TODO
}

extern "C" void I_StartTic()
{
	// TODO
}

extern "C" void I_UpdateNoBlit()
{
	// TODO
}

extern "C" void I_FinishUpdate()
{
	// TODO
}

extern "C" void I_ReadScreen(byte *scr)
{
	memcpy(scr,screens[0],SCREENWIDTH * SCREENHEIGHT);
}

extern "C" void I_SetPalette(byte *palette)
{
	// TODO
}

extern "C" void I_InitGraphics()
{
	// TODO
}
