#include "main.h"
using namespace std;
int Sid[maxs], cnum = 0;
int GetBPrice(int prc,int cur)
{
	return GetItemValue(prc)*GetItemValue(cur);
}

int IsCurr(int id)
{
	switch (id)
	{
		case 18:
		case 22:
			return 1;
	}
	return 0;
}

int GetCurr(int mid)
{
	switch (mid)
	{
	case 11:
		return 22;
	case 14:
	case 18:
	case 21:
		return 18;
	}
}

const char *GetCurrNm(int id)
{
	switch (id)
	{
	case 18:
		return "Sh";
	case 22:
		return "St";
	}
}

void SetSell(int mid)
{
	switch (mid)
	{
	case 11:
		AddSell(15);
		AddSell(40);
		AddSell(48);
		break;
	case 14:
		AddSell(20);
		AddSell(19);
		break;
	case 18:
		AddSell(28);
		AddSell(41);
		AddSell(42);
		break;
	case 21:
		AddSell(46);
		break;
	}
}

void AddSell(int nid)
{
	Sid[cnum] = nid;
	cnum++;
}

void TrReset()
{
	for (int i = 0; i < cnum; i++)
	{
		Sid[i] = 0;
	}
	cnum = 0;
}

void prtsell(int mid)
{
	int curr = GetCurr(mid);
	const char *cn = GetCurrNm(curr);
	while (1)
	{
		clear();
		printw("money:%d %s\n",player.GetInvAmt(curr),cn);
		prtinv();
		printw("Enter number to select,0 to exit.\n");
		refresh();
		int sn = InputNum(30);
		if (sn == 0)
		{
			return;
		}
		int sid = player.slot[sn - 1].id;
		int ta = player.GetInvAmt(sid), tp;
		if (IsCurr(sid))
		{
			msg.print("You can't sell it.");
			continue;
		}
		else
		{
			tp = 0.2 * GetBPrice(sid,curr);
		}
		printw("Price:%d %s\nInput amount to be sold.(total %d)\n", tp,cn, ta);
		refresh();
		int samt = InputNum(ta);
		if (!samt)
		{
			continue;
		}
		msg.print("You sold out %s x%d.", GetItemNm(sid), samt);
		player.DecInv(sid, samt);
		player.AddInv(curr, samt * tp, 0, 0);
	}
}

void prtrd(int mid)
{
	TrReset();
	SetSell(mid);
	int curr = GetCurr(mid), mny = player.GetInvAmt(curr);
	const char *cn = GetCurrNm(curr);
	while (1)
	{
		CmdInit();
		printw("money:%d %s\n", mny, cn);
		for (int i = 0; i < cnum; i++)
		{
			printw("%d.%s %d%s\n", i + 1, GetItemNm(Sid[i]),
				   GetBPrice(Sid[i],curr), cn);
		}
		printw("Enter number to select, or 0 to cancel.\n");
		refresh();
		int tmps = InputNum(cnum + 1);
		if (tmps == 0)
		{
			return;
		}
		tmps--;
		int prc = GetBPrice(Sid[tmps],curr);
		int maxa = mny / prc;
		if (!maxa)
		{
			msg.print("Can't afford this.");
			continue;
		}
		printw("Enter amount(max %d), or 0 to cancel.\n", maxa);
		refresh();
		int namt = InputNum(maxa);
		if (namt == 0)
		{
			return;
		}
		player.DecInv(curr, prc * namt);
		player.AddInv(Sid[tmps], namt, 0, 0);
	}
}