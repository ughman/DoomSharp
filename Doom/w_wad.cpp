using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace DoomSharp;

extern "C"
{
#include "z_zone.h"
}

#include <cstring>
#include <map>
#include <vcclr.h>

extern "C" void W_InitMultipleFiles(char **filenames)
{
	for (;*filenames;filenames++)
	{
		Core::Archives->LoadFile(gcnew String(*filenames));
	}
}

extern "C" int W_CheckNumForName(char *name)
{
	char termname[9];
	termname[8] = 0;
	strncpy(termname,name,8);
	try
	{
		return Core::Archives->Find(gcnew String(termname));
	}
	catch (LumpNotFoundException^)
	{
		return -1;
	}
}

extern "C" int W_GetNumForName(char *name)
{
	char termname[9];
	termname[8] = 0;
	strncpy(termname,name,8);
	return Core::Archives->Find(gcnew String(termname));
}

extern "C" char *W_LumpName(int lump)
{
	static char name[9];
	name[8] = 0;
	char *managedname = (char *)(void *)Marshal::StringToHGlobalAnsi(Core::Archives[lump]->Name);
	strncpy(name,managedname,8);
	Marshal::FreeHGlobal((IntPtr)(void *)managedname);
	return name;
}

extern "C" int W_LumpLength(int lump)
{
	return Core::Archives[lump]->Length;
}

extern "C" void W_ReadLump(int lump,void *dest)
{
	cli::array<unsigned char> ^manageddata = Core::Archives[lump]->Read();
	Marshal::Copy(manageddata,0,(IntPtr)dest,manageddata->Length);
}

extern "C" void *W_CacheLumpNum(int lump,int tag)
{
	static std::map<int,void *> lumpcache;
	void *&lumpdata = lumpcache[lump];
	if (!lumpdata)
	{
		Z_Malloc(W_LumpLength(lump),tag,&lumpdata);
		W_ReadLump(lump,lumpdata);
	}
	else
	{
		Z_ChangeTag2(lumpdata,tag);
	}
	return lumpdata;
}

extern "C" void *W_CacheLumpName(char *name,int tag)
{
	return W_CacheLumpNum(W_GetNumForName(name),tag);
}
