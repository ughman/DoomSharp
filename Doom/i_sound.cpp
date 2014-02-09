using namespace System;
using namespace System::Diagnostics;
using namespace OpenTK;
using namespace OpenTK::Audio;
using namespace OpenTK::Audio::OpenAL;
using namespace DoomSharp;

extern "C"
{
#include "i_sound.h"
#include "w_wad.h"
#include "i_system.h"
}

#include <vcclr.h>
#include <malloc.h>
#include <list>

gcroot<AudioContext^> context;

extern "C" void I_SetChannels()
{
	// TODO
}

extern "C" void I_SetMusicVolume(int volume)
{
	// TODO
}

extern "C" int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)
{
	char name[9];
	name[0] = 'D';
	name[1] = 'S';
	name[8] = 0;
	strncpy(name + 2,sfxinfo->name,6);
	return W_GetNumForName(name);
}

extern "C" int I_StartSound(int id,int vol,int sep,int pitch,int priority)
{
	sfxinfo_t &sfx = S_sfx[id];
	if (!sfx.data)
	{
		int length = W_LumpLength(sfx.lumpnum);
		if (length < 8)
			I_Error("Invalid wave sound length.");
		unsigned char *data = (unsigned char *)_alloca(length);
		W_ReadLump(sfx.lumpnum,data);
		unsigned short samplerate = 0;
		samplerate |= data[2];
		samplerate |= data[3] << 8;
		sfx.data = (void *)AL::GenBuffer();
		AL::BufferData((int)sfx.data,ALFormat::Mono8,(IntPtr)(data + 8),length - 8,samplerate);
	}
	int source = AL::GenSource();
	AL::BindBufferToSource(source,(int)sfx.data);
	I_UpdateSoundParams(source,vol,sep,pitch);
	AL::SourcePlay(source);
	return source;
}

extern "C" void I_StopSound(int handle)
{
	AL::DeleteSource(handle);
}

extern "C" int I_SoundIsPlaying(int handle)
{
	return (AL::GetSourceState(handle) == ALSourceState::Playing);
}

extern "C" void I_UpdateSoundParams(int handle,int vol,int sep,int pitch)
{
	AL::Source(handle,ALSourcef::Gain,vol / 15.0);
}

extern "C" void I_ShutdownSound()
{
	// TODO
}

extern "C" void I_InitSound()
{
	context = gcnew AudioContext();
}

extern "C" void I_InitMusic()
{
}

extern "C" void I_ShutdownMusic()
{
	// TODO
}

extern "C" void I_SubmitSound()
{
}
