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

void CStatdb::DumpRes()
{
	// mob stat
	for (int i = 0; i < mobid; i++, mobc++)
	{
		int cur = GetCurr(i);
		if (cur)
		{
			MobStat[i] = new CMobNPCStatdb;
		}
		else
		{
			MobStat[i] = new CMobStatdb;
		}
		CMobStatdb *ref = (CMobStatdb *) MobStat[i];
		ref->name = GetMobNm(i);
		ref->ht = GetMobMhlth(i);
		ref->mt = 0;
		ref->mlatk = GetMobMatk(i);
		ref->rgatk = GetMobRatk(i);
		ref->mnatk = 0;
		ref->def = GetMobDef(i);
		ref->rng = GetMobRng(i);
		ref->srng = GetMobSrng(i);
		ref->spd = GetMobSpd(i);
		ref->att = GetMobAtt(i);
		ref->size = GetMobSize(i);
		ref->ste = GetMobInitSte(i);
		ref->dexp = GetDe(i);
		// ref->colltyp
		ref->rarity = GetMobRarity(i);
		for (int j = 0; j < 20; j++)
		{
			const char *q = GetMobQuote(i, j);
			if (q == NULL)
			{
				break;
			}
			ref->quote[j] = q;
		}
		ref->drop[0].type = GetDmt(i);
		ref->drop[0].amin = ref->drop[0].amax = GetDm(i);
		ref->drop[0].rate = 100;
		ref->mlbuf.type = GetMobBuff(i);
		ref->mlbuf.val1 = GetMobBuffD(i);
		ref->mlbuf.val2 = GetMobBuffP(i);
		if (cur)
		{
			CMobNPCStatdb *ref2 = (CMobNPCStatdb *) MobStat[i];
			ref2->sellcur = cur;
			TrReset();
			SetSell(i);
			extern int Sid[maxs];
			for (int j = 0; j < maxs; j++)
			{
				if (!Sid[j])
				{
					break;
				}
				ref2->sellid[j] = Sid[j];
			}
		}
	}
	// item stat

	// blkstat

	// bufstat

	// evtstat




}