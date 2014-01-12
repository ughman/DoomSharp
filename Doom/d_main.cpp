using namespace System;
using namespace OpenTK;
using namespace DoomSharp;

extern "C"
{
#include "d_main.h"
#include "g_game.h"
#include "i_video.h"
#include "i_system.h"
#include "m_menu.h"
#include "s_sound.h"
#include "i_sound.h"
#include "doomstat.h"
#include "m_argv.h"
}

#include <vcclr.h>

extern "C" boolean advancedemo;

extern "C" void D_Display();
extern "C" void D_ProcessEvents();
extern "C" void D_DoAdvanceDemo();
extern "C" void G_BuildTiccmd(ticcmd_t *cmd);

void D_DoomTick(Object^ sender,FrameEventArgs^ e);

extern gcroot<MainWindow^> window;

extern "C" void D_DoomLoop()
{
	if (demorecording)
	{
		G_BeginRecording();
	}
	I_InitMusic();
	if (M_CheckParm("-novideo"))
	{
		while (true)
		{
			D_DoomTick(nullptr,nullptr);
		}
	}
	else
	{
		I_InitGraphics();
		window->UpdateFrame += gcnew EventHandler<FrameEventArgs^>(D_DoomTick);
		window->Run();
	}
}

void D_DoomTick(Object^ sender,FrameEventArgs^ e)
{
	I_StartFrame();
	if (singletics)
	{
		I_StartTic();
		D_ProcessEvents();
		G_BuildTiccmd(&netcmds[consoleplayer][maketic%BACKUPTICS]);
		if (advancedemo)
		{
			D_DoAdvanceDemo();
		}
		M_Ticker();
		G_Ticker();
		gametic++;
		maketic++;
	}
	else
	{
		TryRunTics();
	}
	S_UpdateSounds(players[consoleplayer].mo);
	if (!M_CheckParm("-novideo"))
		D_Display();
	I_SubmitSound();
}
