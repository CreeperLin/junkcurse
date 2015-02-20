#include "main.h"
using namespace std;
void CWorld::EraUpdate()
{
	msg.print("Era %d has come.",++era);
	msg.SetAttr(12);
	switch (era)
	{
		case 0:
		return;
		case 1:
		ClrBlk(14,1);
		GenVillages(50);
		break;
		case 2:
		ClrBlk(11,2);
		ClrBlk(12,5);
		ClrBlk(13,5);
		break;
	}
}

void CWorld::Reset()
{
	era=0;
	seed = 0;
	wspn.Reset();
	ppbr = 100;
	pcwd = 60;
	ppa = 25;
	pdc = 40;
	cwdt = 0;
	dct = 0;
	nwthr = 0;
	nrain = 0;
	nievt = 0;
	nmist = 0;
	WipeEventa();
}

void CWorld::Init()
{
	sprintf(name, "World 1");
	seed = time(0);
	msg.print("seed %ld", seed);
	srand(seed);
}

void CWorld::Update()
{
	while (tm.d>GetEraStart(era+1)&&era<7)
	{
		EraUpdate();
	}
}

void CWorld::AdjGaP(int &p, int n)
{
	p += n;
	if (p > 100)
	{
		p = 100;
	}
	else if (p < 0)
	{
		p = 0;
	}
}

int CWorld::GetCpwdP()
{
	return pcwd;
}

int CWorld::GetPbrP()
{
	return ppbr;
}

int CWorld::GetPaP()
{
	return ppa;
}

int CWorld::GetDcP()
{
	return pdc;
}

int CWorld::Chop()
{
	switch (blk[player.p.geti()])
	{
	case 2:
	case 8:
		if (Prob(GetCpwdP()))
		{
			int amt = randr(3, 5);
			player.AddInv(8, amt, 0, 0);
			cwdt++;
			if (cwdt == 5)
			{
				cwdt = 0;
				AdjGaP(pcwd, -1);
			}
		}
		else
		{
			msg.print("You've got nothing.");
		}
		tm.Adj(20, 0, 0);
		Refresh();
		return 1;
	}
	msg.print("There's nothing for you to chop.");
	return 0;
}

int CWorld::Pick()
{
	switch (blk[player.p.geti()])
	{
	case 2:
		if (Prob(GetPaP()))
		{
			int amt = randr(1, 2);
			player.AddInv(16, amt, 0, 0);
			AdjGaP(ppa, -1);
		}
		else
		{
			msg.print("You've got nothing.");
		}
		tm.Adj(20, 0, 0);
		return 1;
	case 9:
		if (Prob(GetPbrP()))
		{
			int amt = randr(4, 8);
			player.AddInv(17, amt, 0, 0);
			AdjGaP(ppbr, -1);
		}
		else
		{
			msg.print("You've got nothing.");
		}
		tm.Adj(20, 0, 0);
		Refresh();
		return 1;
	}
	msg.print("There's nothing for you to pick.");
	return 0;
}

int CWorld::Dig()
{
	switch (blk[player.p.geti()])
	{
	case 5:
	case 6:
		if (Prob(GetDcP()))
		{
			int amt = randr(1, 5);
			player.AddInv(31, amt, 0, 0);
			dct++;
			if (dct == 10)
			{
				dct = 0;
				AdjGaP(pdc, -1);
			}
		}
		else
		{
			msg.print("You've got nothing.");
		}
		tm.Adj(20, 0, 0);
		Refresh();
		return 1;
	}
	msg.print("There's nothing for you to dig.");
	return 0;
}

void CWorld::InitEvent()
{
	WipeEventa();
	int p = rand() % 100;
	if (p < 10)
	{
		AddEvent(4, randr(36, 72));
	}
	else if (p < 30)
	{
		AddEvent(1, randr(150, 200));
	}
}

int CWorld::EventUpdate()
{
	for (int i = 0; i < evtn; i++)
	{
		int tid = wtimer[i].id;
		switch (tid)
		{
		case 0:
			continue;
		case 5:
			pos lp;
			lp.Set(randr(0, wlth - 1), randr(0, wlth - 1));
			if (lp == player.p)
			{
				player.Adjhlth(-20, 4, 1);
			}
			for (int i = 0; i < mobn; i++)
			{
				if (mob[i].p == lp)
				{
					if (mob[i].Adjhlth(-20, 4, 1))
					{
						mob[i].Reset();
					}
				}
			}
			break;
		}
		if (wtimer[i].Tick())
		{
			switch (tid)
			{
			case 1:
				msg.print("The rain has stopped.");
				break;
			case 2:
				msg.print("The torrent has stopped.");
				break;
			case 3:
				msg.print("The snow has stopped.");
				break;
			case 4:
				msg.print("Your sight were widened as the mist lifted.");
				break;
			case 5:
				msg.print("The sky stopped roaring.");
				break;
			default:
				msg.print("blah blah stopped.");
				break;
			}
			msg.SetAttr(13);
		}
	}
	return 0;
}

void CWorld::WipeEvent(int nid)
{
	for (int i = 0; i < evtn; i++)
	{
		if (nid)
		{
			wtimer[i].Reset();
			return;
		}
	}
}

void CWorld::WipeEventa()
{
	for (int i = 0; i < evtn; i++)
	{
		wtimer[i].Reset();
	}
}

int CWorld::IsEvent(int nid)
{
	for (int i = 0; i < evtn; i++)
	{
		if (wtimer[i].id == nid)
		{
			return 1;
		}
	}
	return 0;
}

void CWorld::AddEvent(int nid, int nintv)
{
	for (int i = 0; i < evtn; i++)
	{
		if (!wtimer[i].id)
		{
			wtimer[i].Set(nid, nintv);
			switch (nid)
			{
			case 1:
				msg.print("The Rain began to fall.");
				break;
			case 2:
				msg.print("The water is pouring from the sky.");
				break;
			case 3:
				msg.print("Millions of snowflakes.");
				break;
			case 4:
				msg.print("The world was shrouded in mist");
				break;
			case 5:
				msg.print("The sky began to roar.");
				break;
			}
			msg.SetAttr(12);
			return;
		}
	}
}

void CWorld::EventProducer()
{
	if (nmist >= 3)
	{
		if (tm.h >= 6 && tm.h <= 8 && Prob(20))
		{
			AddEvent(4, randr(36, 72));
			nmist = 0;
		}
	}
	if (nwthr >= 7)
	{
		if (Prob(40))
		{
			int wtype = 0;
			int dur = randr(150, 200);
			switch (tm.GetSe())
			{
			case 1:
				wtype = 1;
				break;
			case 2:
				wtype = randr(1, 2);
				break;
			case 3:
				wtype = randr(1, 2);
				break;
			case 4:
				wtype = (rand() % 2) ? 3 : 1;
				break;
			}
			AddEvent(wtype, dur);
			nrain++;
			switch (wtype)
			{
			case 1:
			case 2:
				if (wtype == 1)
				{
					AdjGaP(pcwd, 5);
					AdjGaP(ppbr, 5);
				}
				nrain = 0;
				if (Prob(20))
				{
					AddEvent(5, dur);
				}
				break;
			}
			nwthr = 0;
		}
		nievt++;
		if (nievt >= 2)
		{
			switch (tm.GetSe())
			{
			case 1:
			case 2:
				if (IsEvent(1))
				{
					AdjGaP(pcwd, 10);
					AdjGaP(ppbr, 5);
					msg.print("The Rain has brought growth to the world.");
				}
				else if (nrain >= 3)
				{
					AdjGaP(ppbr, -15);
					AdjGaP(ppa, -15);
					msg.print("Plants are dying for water.");
				}
				break;
			case 3:
				AdjGaP(ppa, 20);
				msg.print("Time to harvest.");
				break;
			}
			msg.SetAttr(12);
			nievt = 0;
		}
	}
}