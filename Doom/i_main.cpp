using namespace System;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace DoomSharp;

extern "C"
{
#include "m_argv.h"
#include "d_main.h"
}

#include <stdlib.h>

void I_StatTest(String^ dir,String ^game,StreamWriter^ log)
{
	if (!game->CompareTo(gcnew String("pwad")))
		return;
	DirectoryInfo^ dirinfo = gcnew DirectoryInfo(dir);
	for each (DirectoryInfo^ subdir in dirinfo->GetDirectories())
	{
		I_StatTest(Path::Combine(dir,subdir->Name),game,log);
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
			String^ args = String::Format("-{0} -timedemo StatDemo -statcopy {1} -novideo -noerror",game,output);
			ProcessStartInfo psi(exe,args);
			psi.UseShellExecute = false;
			psi.RedirectStandardOutput = true;
			psi.RedirectStandardError = true;
			psi.WorkingDirectory = Directory::GetCurrentDirectory();
			psi.ErrorDialog = false;
			Process^ process = Process::Start(%psi);
			//process->StandardOutput->ReadToEnd();
			//process->StandardError->ReadToEnd();
			if (process->WaitForExit(25000))
			{
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
						log->WriteLine("[FAIL] {0}",Path::Combine(dir,file->Name));
						Console::Write("[");
						Console::ForegroundColor = ConsoleColor::Red;
						Console::Write("FAIL");
						Console::ResetColor();
						Console::WriteLine("]");
					}
				}
				else if (process->ExitCode == 0xDEAD33)
				{
					log->WriteLine("[BADV] {0}",Path::Combine(dir,file->Name));
					Console::Write("[");
					Console::ForegroundColor = ConsoleColor::Cyan;
					Console::Write("BADV");
					Console::ResetColor();
					Console::WriteLine("]");
				}
				else
				{
					log->WriteLine("[CRSH] {0}",Path::Combine(dir,file->Name));
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
				process->Kill();
				Thread::Sleep(5000);
				log->WriteLine("[2SLO] {0}",Path::Combine(dir,file->Name));
				Console::Write("[");
				Console::ForegroundColor = ConsoleColor::Black;
				Console::BackgroundColor = ConsoleColor::Yellow;
				Console::Write("2SLO");
				Console::ResetColor();
				Console::WriteLine("]");
			}
		}
		else
		{
			log->WriteLine("[LMP?] {0}",Path::Combine(dir,file->Name));
			Console::Write("[");
			Console::ForegroundColor = ConsoleColor::Yellow;
			Console::Write("LMP?");
			Console::ResetColor();
			Console::WriteLine("]");
		}
		log->Flush();
	}
}

void I_StatTestRoot(String^ dir,StreamWriter^ log)
{
	DirectoryInfo^ dirinfo = gcnew DirectoryInfo(dir);
	for each (DirectoryInfo^ subdir in dirinfo->GetDirectories())
	{
		I_StatTest(Path::Combine(dir,subdir->Name),subdir->Name,log);
	}
}

void I_UnhandledException(Object^ sender,UnhandledExceptionEventArgs^ e)
{
	exit(123);
}

int main(int argc,char **argv)
{
	myargc = argc;
	myargv = argv;
	Registrar::RegisterAssembly(Assembly::Load("DoomSharp"));
	Registrar::RegisterAssembly(Assembly::GetExecutingAssembly());
	if (M_CheckParm("-noerror"))
	{
		AppDomain::CurrentDomain->UnhandledException += gcnew UnhandledExceptionEventHandler(I_UnhandledException);
	}
	if (int p = M_CheckParm("-server"))
	{
		long port = strtol(myargv[p + 1],NULL,10);
		long nodecount = strtol(myargv[p + 2],NULL,10);
		(gcnew DoomServer(port))->Run(nodecount);
		return 0;
	}
	if (M_CheckParm("-stattest"))
	{
		FileStream logstream(gcnew String("TestLog.txt"),FileMode::Create,FileAccess::Write);
		StreamWriter log(%logstream);
		I_StatTestRoot(gcnew String("Tests"),%log);
		return 0;
	}
	D_DoomMain();
}
