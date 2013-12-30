using namespace System;
using namespace DoomSharp;

extern "C"
{
#include "i_video.h"
#include "v_video.h"
}

#include <vcclr.h>

gcroot<MainWindow^> window;

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
	window->SubmitFrame((IntPtr)screens[0]);
}

extern "C" void I_ReadScreen(byte *scr)
{
	memcpy(scr,screens[0],SCREENWIDTH * SCREENHEIGHT);
}

extern "C" void I_SetPalette(byte *palette)
{
	window->SubmitPalette((IntPtr)palette);
}

extern "C" void I_InitGraphics()
{
	window = MainWindow::RunAsync();
}
