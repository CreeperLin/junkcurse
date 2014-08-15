#include "main.h"
using namespace std;
void item::Reset()
{
	id = 0;
	amt = 0;
	lvl = 0;
	mod = 0;
	plc = 0;
	p.Reset();
	for (int i = 0; i < pnum; i++)
	{
		pid[i] = 0;
		pamt[i] = 0;
	}
}

void item::Set(int nid, int namt, int nlvl, int nmod, int nplc, pos np)
{
	id = nid;
	amt = namt;
	lvl = nlvl;
	mod = nmod;
	plc = nplc;
	p = np;
}

int IsItemNear(pos p, int isp)
{
	for (int i = 0; i < inum; i++)
	{
		if (witem[i].plc == isp && witem[i].p == player.p)
		{
			return 1;
		}
	}
	return 0;
}

int IsItemArnd(int nid)
{
	for (int i = 0; i < inum; i++)
	{
		if (witem[i].id == nid && witem[i].plc&&witem[i].p + player.p <= 2&&!IsColls(witem[i].p,player.p))
		{
			return 1;
		}
	}
	return 0;
}

int IsItemNear(pos p, int isp, int nid)
{
	for (int i = 0; i < inum; i++)
	{
		if (witem[i].id == nid && witem[i].plc == isp
			&& witem[i].p == player.p)
		{
			return 1;
		}
	}
	return 0;
}

void AddItem(int nid, int namt, int nlvl, int nmod, int nplc, pos np)
{
	for (int i = 0; i < inum; i++)
	{
		if (witem[i].id == 0)
		{
			witem[i].Set(nid, namt, nlvl, nmod, nplc, np);
			break;
		}
	}
}