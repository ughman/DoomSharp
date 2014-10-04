using namespace System;
using namespace DoomSharp;

extern "C"
{
#include "s_sound.h"
#include "sounds.h"
#include "m_argv.h"
}

#include <cstring>

extern "C" void S_StartMusic(int musicnum)
{
	S_ChangeMusic(musicnum,false);
}

extern "C" void S_ChangeMusic(int musicnum,int looping)
{
	char name[9];
	strcpy(name,"D_");
	strcat(name,S_music[musicnum].name);
	Core::Music->Play(gcnew String(name),looping);
}

extern "C" void S_StopMusic()
{
	Core::Music->Stop();
}
