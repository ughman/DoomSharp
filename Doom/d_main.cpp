using namespace System;
using namespace OpenTK;
using namespace OpenTK::Input;
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

void D_DoomTick();
int TranslateKey(Key key);

ref class LegacyGameState : GameState
{
public:
	virtual void Update(double time,bool top) override
	{
		if (top)
			D_DoomTick();
	}

	virtual void KeyDown(Key key) override
	{
		event_t ev;
		ev.type = ev_keydown;
		ev.data1 = TranslateKey(key);
		D_PostEvent(&ev);
	}

	virtual void KeyUp(Key key) override
	{
		event_t ev;
		ev.type = ev_keyup;
		ev.data1 = TranslateKey(key);
		D_PostEvent(&ev);
	}
};

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
			D_DoomTick();
		}
	}
	else
	{
		Core::PushState(gcnew LegacyGameState);
		I_InitGraphics();
		Core::Video->Run();
	}
}

void D_DoomTick()
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
	if (!M_CheckParm("-novideo") && fastforward <= gamemap)
		D_Display();
	I_SubmitSound();
}
