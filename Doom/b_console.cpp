using namespace System;
using namespace DoomSharp;

extern "C" void B_LogError(const char *message)
{
	Core::Console->LogError(gcnew String(message));
}

extern "C" void B_LogWarning(const char *message)
{
	Core::Console->LogWarning(gcnew String(message));
}

extern "C" void B_LogGameMessage(const char *message)
{
	Core::Console->LogGameMessage(gcnew String(message));
}
