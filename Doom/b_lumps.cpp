using namespace System;
using namespace System::Collections::Generic;
using namespace DoomSharp;

#include <vcclr.h>

extern gcroot<MultiArchive^> archives;

gcroot<List<int>^> spritelumps;
int spritelumpiterator;

void B_InitLumps2()
{
	spritelumps = gcnew List<int>();
	String^ name_s_start = gcnew String("S_START");
	String^ name_s_end = gcnew String("S_END");
	String^ name_ss_start = gcnew String("SS_START");
	String^ name_ss_end = gcnew String("SS_END");
	bool inspritezone = false;
	for (int i = 0;i < archives->LumpCount;i++)
	{
		ILump^ lump = archives->default[i];
		if (lump->Name == name_s_start || lump->Name == name_ss_start)
		{
			inspritezone = true;
		}
		else if (lump->Name == name_s_end || lump->Name == name_ss_end)
		{
			inspritezone = false;
		}
		else if (inspritezone)
		{
			spritelumps->Add(i);
		}
	}
}

extern "C" void B_InitLumps()
{
	B_InitLumps2();
}

extern "C" void B_ResetSpriteLumpIterator()
{
	spritelumpiterator = 0;
}

extern "C" int B_NextSpriteLump()
{
	if (spritelumps->Count > spritelumpiterator)
	{
		return spritelumps->default[spritelumpiterator++];
	}
	else
	{
		return -1;
	}
}
