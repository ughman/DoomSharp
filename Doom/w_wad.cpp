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

gcroot<MultiArchive^> archives;

extern "C" void W_Reload()
{
}

extern "C" void W_InitMultipleFiles(char **filenames)
{
	if (!archives)
	{
		archives = gcnew MultiArchive();
	}
	for (;*filenames;filenames++)
	{
		FileStream ^stream = gcnew FileStream(gcnew String(*filenames),FileMode::Open,FileAccess::Read);
		WadArchive ^archive = gcnew WadArchive(stream);
		archives->AddArchive(archive);
	}
}

extern "C" int W_CheckNumForName(char *name)
{
	try
	{
		return archives->Find(gcnew String(name));
	}
	catch (LumpNotFoundException^)
	{
		return -1;
	}
}

extern "C" int W_GetNumForName(char *name)
{
	return archives->Find(gcnew String(name));
}

extern "C" char *W_LumpName(int lump)
{
	static char name[9];
	name[8] = 0;
	char *managedname = (char *)(void *)Marshal::StringToHGlobalAnsi(archives->default[lump]->Name);
	strncpy(name,managedname,8);
	Marshal::FreeHGlobal((IntPtr)(void *)managedname);
	return name;
}

extern "C" int W_LumpLength(int lump)
{
	return archives->default[lump]->Length;
}

extern "C" void W_ReadLump(int lump,void *dest)
{
	cli::array<unsigned char> ^manageddata = archives->default[lump]->Read();
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
