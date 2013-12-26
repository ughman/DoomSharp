extern "C"
{
#include "i_net.h"
#include "d_net.h"
#include "doomstat.h"
}

extern "C" void I_InitNetwork()
{
	doomcom = new doomcom_t;
	memset(doomcom,0,sizeof(doomcom_t));
	doomcom->ticdup = 1;
	netgame = false;
	doomcom->id = DOOMCOM_ID;
	doomcom->numplayers = doomcom->numnodes = 1;
	// TODO
}

extern "C" void I_NetCmd()
{
	// TODO
}
