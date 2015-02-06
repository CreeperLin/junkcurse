#include "main.h"
using namespace std;
int inv::Decraft(int n)
{
	if (pid[n])
	{
		player.AddInv(pid[n], pamt[n], 0, 0);
		pid[n] = 0;
		pamt[n] = 0;
		return 1;
	}
	msg.print("cannot decraft.");
	return 0;
}

int inv::Decrafta()
{
	int isd = 0;
	for (int i = 0; i < pnum; i++)
	{
		if (pid[i])
		{
			player.AddInv(pid[i], pamt[i], 0, 0);
			isd = 1;
		}
	}
	if (isd)
	{
		Adj(-1);
		return 1;
	}
	msg.print("cannot decraft.");
	return 0;
}

int inv::Adapt(int cnum)
{
	if (!player.slot[cnum].IsAdable(id))
	{
		msg.print("cannot adapt.");
		return 0;
	}
	for (int i = 1; i < pnum; i++)
	{
		if (player.slot[cnum].pid[i])
		{
			continue;
		}
		int tid = player.slot[cnum].id;
		if (tid != -1)
		{
			player.slot[cnum].pid[0] = tid;
			player.slot[cnum].id = -1;
			player.slot[cnum].pamt[0] = 1;
		}
		player.slot[cnum].pid[i] = id;
		player.slot[cnum].pamt[i]++;
		Adj(-1);
		return 1;
	}
	msg.print("cannot adapt more.");
	return 0;
}

void inv::Reset()
{
	id = 0;
	amt = 0;
	lvl = 0;
	mod = 0;
	for (int i = 0; i < pnum; i++)
	{
		pid[i] = 0;
		pamt[i] = 0;
	}
}

void inv::Adj(int namt)
{
	amt += namt;
	if (amt <= 0)
	{
		Reset();
		return;
	}
	int tmax = GetItemMxstk(id);
	if (amt > tmax)
	{
		amt = tmax;
	}
}