extern "C"
{
#include "i_sound.h"
}

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
	// TODO
	return 0;
}

extern "C" int I_StartSound(int id,int vol,int sep,int pitch,int priority)
{
	// TODO
	return 0;
}

extern "C" void I_StopSound(int handle)
{
	// TODO
}

extern "C" int I_SoundIsPlaying(int handle)
{
	// TODO
	return 0;
}

extern "C" void I_SubmitSound()
{
	// TODO
}

extern "C" void I_UpdateSoundParams(int handle,int vol,int sep,int pitch)
{
	// TODO
}

extern "C" void I_ShutdownSound()
{
	// TODO
}

extern "C" void I_InitSound()
{
	// TODO
}

extern "C" void I_InitMusic()
{
	// TODO
}

extern "C" void I_ShutdownMusic()
{
	// TODO
}

extern "C" void I_PlaySong(int handle,int looping)
{
	// TODO
}

extern "C" void I_PauseSong(int handle)
{
	// TODO
}

extern "C" void I_ResumeSong(int handle)
{
	// TODO
}

extern "C" void I_StopSong(int handle)
{
	// TODO
}

extern "C" void I_UnRegisterSong(int handle)
{
	// TODO
}

extern "C" int I_RegisterSong(void *data)
{
	// TODO
	return 0;
}
