using namespace System;
using namespace System::Collections::Generic;
using namespace DoomSharp;

#include <vcclr.h>

gcroot<List<int>^> spritelumps;
int spritelumpiterator;
gcroot<List<int>^> flatlumps;

void B_InitLumps2()
{
	spritelumps = gcnew List<int>();
	flatlumps = gcnew List<int>();
	String^ name_s_start = gcnew String("S_START");
	String^ name_s_end = gcnew String("S_END");
	String^ name_ss_start = gcnew String("SS_START");
	String^ name_ss_end = gcnew String("SS_END");
	String^ name_f_start = gcnew String("F_START");
	String^ name_f_end = gcnew String("F_END");
	String^ name_ff_start = gcnew String("FF_START");
	String^ name_ff_end = gcnew String("FF_END");
	bool inspritezone = false;
	bool inflatzone = false;
	for (int i = 0;i < Core::Archives->LumpCount;i++)
	{
		ILump^ lump = Core::Archives[i];
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
		if (lump->Name == name_f_start || lump->Name == name_ff_start)
		{
			inflatzone = true;
		}
		else if (lump->Name == name_f_end || lump->Name == name_ff_end)
		{
			inflatzone = false;
		}
		else if (inflatzone)
		{
			flatlumps->Add(i);
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
