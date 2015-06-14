#include "main.h"
using namespace std;

void CStatdb::Reset()
{
	mobc = itmc = blkc = bufc = evtc = 0;
	for (int i = 0; i < mobid; i++)
	{
		delete MobStat[i];
	}
	for (int i = 0; i < itmid; i++)
	{
		delete ItemStat[i];
	}
	for (int i = 0; i < blkid; i++)
	{
		delete BlkStat[i];
	}
	for (int i = 0; i < bufid; i++)
	{
		delete BufStat[i];
	}
	for (int i = 0; i < evtid; i++)
	{
		delete EventStat[i];
	}
}