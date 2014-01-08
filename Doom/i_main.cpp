using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;

extern "C"
{
#include "m_argv.h"
#include "d_main.h"
}

void I_StatTest(String^ dir,String ^game)
{
	if (!game->CompareTo(gcnew String("pwad")))
		return;
	DirectoryInfo^ dirinfo = gcnew DirectoryInfo(dir);
	for each (DirectoryInfo^ subdir in dirinfo->GetDirectories())
	{
		I_StatTest(Path::Combine(dir,subdir->Name),game);
	}
	for each (FileInfo^ file in dirinfo->GetFiles())
	{
		if (file->Extension->ToLower() != ".txt")
			continue;
		String^ demofile = Path::ChangeExtension(file->FullName,".lmp");
		Console::Write(Path::Combine(dir,file->Name)->PadRight(73,'.'));
		String^ output = gcnew String("StatTestOutput.txt");
		String^ tempdemo = gcnew String("StatDemo.lmp");
		File::WriteAllBytes(output,gcnew array<unsigned char>(0));
		if (File::Exists(tempdemo))
			File::Delete(tempdemo);
		if (File::Exists(demofile))
		{
			File::Copy(demofile,tempdemo);
			String^ exe = Assembly::GetExecutingAssembly()->Location;
			String^ args = String::Format("-{0} -timedemo StatDemo -statcopy {1} -novideo",game,output);
			ProcessStartInfo psi(exe,args);
			psi.UseShellExecute = false;
			psi.RedirectStandardOutput = true;
			psi.RedirectStandardError = true;
			psi.WorkingDirectory = Directory::GetCurrentDirectory();
			psi.ErrorDialog = false;
			Process^ process = Process::Start(%psi);
			process->StandardOutput->ReadToEnd();
			process->StandardError->ReadToEnd();
			process->WaitForExit();
			if (process->ExitCode == 0)
			{
				array<unsigned char>^ vstats = File::ReadAllBytes(file->FullName);
				array<unsigned char>^ newstats = File::ReadAllBytes(output);
				bool correct = vstats->Length == newstats->Length;
				if (correct)
				{
					for (int i = 0;i < newstats->Length;i++)
					{
						if (newstats[i] != vstats[i])
						{
							correct = false;
							break;
						}
					}
				}
				if (correct)
				{
					Console::Write("[");
					Console::ForegroundColor = ConsoleColor::Green;
					Console::Write(" OK ");
					Console::ResetColor();
					Console::WriteLine("]");
				}
				else
				{
					Console::Write("[");
					Console::ForegroundColor = ConsoleColor::Red;
					Console::Write("FAIL");
					Console::ResetColor();
					Console::WriteLine("]");
				}
			}
			else if (process->ExitCode == 0xDEAD33)
			{
				Console::Write("[");
				Console::ForegroundColor = ConsoleColor::Cyan;
				Console::Write("BADV");
				Console::ResetColor();
				Console::WriteLine("]");
			}
			else
			{
				Console::Write("[");
				Console::ForegroundColor = ConsoleColor::White;
				Console::BackgroundColor = ConsoleColor::Red;
				Console::Write("CRSH");
				Console::ResetColor();
				Console::WriteLine("]");
			}
		}
		else
		{
			Console::Write("[");
			Console::ForegroundColor = ConsoleColor::Yellow;
			Console::Write("LMP?");
			Console::ResetColor();
			Console::WriteLine("]");
		}
	}
}

void I_StatTestRoot(String^ dir)
{
	DirectoryInfo^ dirinfo = gcnew DirectoryInfo(dir);
	for each (DirectoryInfo^ subdir in dirinfo->GetDirectories())
	{
		I_StatTest(Path::Combine(dir,subdir->Name),subdir->Name);
	}
}

int main(int argc,char **argv)
{
	myargc = argc;
	myargv = argv;
	if (M_CheckParm("-stattest"))
	{
		I_StatTestRoot(gcnew String("Tests"));
		return 0;
	}
	D_DoomMain();
}
