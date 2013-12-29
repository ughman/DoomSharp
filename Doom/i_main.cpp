extern "C"
{
#include "m_argv.h"
#include "d_main.h"
}

int main(int argc,char **argv)
{
	myargc = argc;
	myargv = argv;
	D_DoomMain();
}
