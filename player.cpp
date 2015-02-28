#include "main.h"
using namespace std;
int fbio, phl = 3, pml = 2;
void CPlayer::Collect()
{
	int isrmv = 0;
	for (int i = 0; i < inum; i++)
	{
		if (world.witem[i].id && !world.witem[i].plc && world.witem[i].p + p <= 2)
		{
			msg.print("You picked up %s x%d.", GetItemNm(world.witem[i].id),
				   world.witem[i].amt);
			AddInv(world.witem[i].id, world.witem[i].amt, world.witem[i].lvl, world.witem[i].mod);
			world.witem[i].Reset();
			isrmv = 1;
		}
	}
	if (!isrmv)
	{
		msg.print("You picked up nothing.");
		return;
	}
	tm.Adj(1, 0, 0);
	Refresh();
}

void CPlayer::Remove()
{
	int isrmv = 0;
	for (int i = 0; i < 100; i++)
	{
		if (world.witem[i].id && world.witem[i].plc && world.witem[i].p == p)
		{
			msg.print("You removed a %s.", GetItemNm(world.witem[i].id));
			AddInv(world.witem[i].id, 1, 0, 0);
			world.witem[i].Reset();
			if (spn == p && spn != world.wspn)
			{
				spn = world.wspn;
				msg.print("Spawnpoint Reset!");
			}
			isrmv = 1;
		}
	}
	if (!isrmv)
	{
		msg.print("You removed nothing.");
		return;
	}
	tm.Adj(1, 0, 0);
	Refresh();
}


void CPlayer::Kill()
{
	int dist = 0, tmpn = 0;
	if (ptgt && mob[ptgt - 1].id)
	{
		tmpn = ptgt - 1;
		dist = p + mob[tmpn].p;
		if (dist > GetRng() || IsColls(p, mob[tmpn].p))
		{
			if (dist > GetSrng())
			{
				ptgt = 0;
			}
			msg.print("Can't reach that.");
			return;
		}
	}
	else
	{
		ptgt = 0;
		tmpn = prtmb(min(GetSrng(), GetRng()));
		if (tmpn < 0)
		{
			if (tmpn == -1)
			{
				msg.print("There's no one for you to kill.");
			}
			return;
		}
		ptgt = tmpn + 1;
		dist = p + mob[tmpn].p;
	}
	int isa = 0;
	for (int i = 0; i < 2; i++)
	{
		if (!slot[i].IsArm() && !i)
		{
			continue;
		}
		int patk = GetAtk(i);
		if (!patk)
		{
			continue;
		}
		isa = 1;
		for (int j = 0; j < mobn; j++)
		{
			if (j != tmpn && mob[j].id == mob[tmpn].id
				&& p + mob[j].p <= mob[j].GetSrng() && !IsColls(p, mob[j].p))
			{
				mob[j].AIFb(2, -1);
			}
		}
		int wid = slot[i].id;
		switch (slot[i].type())
		{
		case 9:
			{
				int atype = GetAmmoType(wid);
				if (GetInvAmt(atype) <= 10)
				DecInv(atype, 1);
				{
					msg.print(15, "Low ammo");
				}
			}
			break;
		case 10:
			Adjmana(-GetMpc(wid), 0, 0);
			if (mp <= 5 * GetMpc(wid))
			{
				msg.print(15, "Low mana");
			}
		}
		if (mob[tmpn].Adjhlth
			(AtkCnt(patk, mob[tmpn].GetDef(), GetCc(i)), 1, -1))
		{
			mob[tmpn].Drop();
			mob[tmpn].Reset();
			tm.Adj(1, 0, 0);
			Refresh();
			return;
		}
		switch (wid)			// effect
		{
		case 44:
			Explode(mob[tmpn].p, wid);
			break;
		default:
			{
				int bid = GetItemBuff(wid);
				if (bid && Prob(GetItemBuffP(wid)))
				{
					mob[tmpn].Addbuff(bid, GetItemBuffD(wid), -1);
				}
			}
		}
		break;
	}
	if (!isa)
	{
		return;
	}
	if (dist <= mob[tmpn].GetSrng() + GetAtt() && !IsColls(mob[tmpn].p, p))
	{
		mob[tmpn].AIFb(1, -1);
	}
	tm.Adj(1, 0, 0);
	Refresh();
}

void CPlayer::Talk()
{
	int tnum = prtmb(2);
	if (tnum < 0)
	{
		if (tnum == -1)
		{
			msg.print("There's no one to talk to.");
		}
		return;
	}
	int sel;
	switch (mob[tnum].Speak(0))
	{
	case 0:
		break;
	case 1:
		msg.Show();
		CmdInit();
	printw("You:\n1.Buy\n2.Sell\n0.Leave\n");
		refresh();
		sel = InputNum(2);
		switch (sel)
		{
		case 0:
			mob[tnum].Speak(2);
			break;
		case 1:
			mob[tnum].Speak(1);
			msg.Show();
			prtrd(mob[tnum].id);
			mob[tnum].Speak(2);
			break;
		case 2:
			prtsell(mob[tnum].id);
			mob[tnum].Speak(2);
			break;
		}
		break;
	}
	tm.Adj(5, 0, 0);
	Refresh();
}

void CPlayer::Inv()
{
	int tiid, tmpi;
  loop1:
	clear();
	prtinv();
	while (1)
	{
		msg.Show();	
		refresh();	
		if (getch() == key[9])
		{
			return;
		}
		CmdInit();
		printw("Enter number to select,0 to exit.\n");
		refresh();
		tmpi = InputNum(30);
		if (tmpi == 0)
		{
			return;
		}
		tmpi--;
		tiid = slot[tmpi].id;
		if (!tiid)
		{
			msg.print("You've select nothing.");
			continue;
		}
		break;
	}
	int ttp = slot[tmpi].type();
	while (1)
	{
		int tia = slot[tmpi].amt;
		clear();
		prtinv();
		msg.Show();	
		CmdInit();
		printw("You've selected %s x%d.\n1.use 2.place 3.equip/dequip\n4.grab 5.throw 6.adapt 7.decraft 0.exit.\n", GetItemNm(tiid), tia);
		refresh();
		int tmpfx = InputNum(8);
		if (tmpfx == 0)
		{
			return;
		}
		switch (tmpfx)
		{
		case 1:
			switch (ttp)
			{
			case 1:
				Adjhlth(GetItemFd(tiid), 3, tiid);
				break;
			case 11:
				Adjmana(GetItemFm(tiid), 3, tiid);
				break;
			default:
				if (tiid == 31)
				{
					Explode(p, tiid);
				}
				else
				{
					msg.print("Can't do that.");
					continue;
				}
			}
			slot[tmpi].Adj(-1);
			break;
		case 2:
			if (ttp != 2)
			{
				msg.print("Can't do that.");
				continue;
			}
			if (IsBlkPlc(blk[p.geti()]) && !IsItemNear(p, 1))
			{
				AddItem(tiid, 1, 0, 0, 1, p);
				msg.print("You've placed a %s.", GetItemNm(slot[tmpi].id));
				slot[tmpi].Adj(-1);
			}
			else
			{
				msg.print("Can't be placed.");
				continue;
			}
			break;
		case 3:
			if (tmpi > 1 && tmpi < 10)
			{
				Unequip(tmpi);
				msg.print("You took your %s off.", GetItemNm(tiid));
			}
			else
			{
				switch (ttp)
				{
				case 3:
				case 4:
				case 5:
				case 6:
					SwapInv(ttp - 1, tmpi);
					msg.print("You put %s on.", GetItemNm(tiid));
					break;
				case 7:
					{
						int iseq = 0;
						for (int i = 6; i < 10; i++)
						{
							if (!slot[i].id)
							{
								SwapInv(i, tmpi);
								msg.print("You equipped %s.", GetItemNm(tiid));
								iseq = 1;
								break;
							}
						}
						if (!iseq)
						{
							SwapInv(randr(6, 9), tmpi);
							msg.print("You equipped %s.", GetItemNm(tiid));
						}
					}
					break;
				default:
					msg.print("Can't do that.");
					continue;
				}
			}
			break;
		case 4:
			if (tmpi < 2)
			{
				Unequip(tmpi);
				msg.print("You've took %s x%d off.", GetItemNm(tiid), tia);
				break;
			}
			if (!slot[0].id)
			{
				if (slot[tmpi].size() == 2)
				{
					if (slot[1].id)
					{
						Unequip(1);
					}
				}
				else if (slot[1].id == tiid)
				{
					AddInv(1, tiid, tia, 0, 0);
					slot[tmpi].Reset();
				}
				else if (slot[1].IsArm())
				{
					Unequip(1);
				}
				SwapInv(0, tmpi);
			}
			else
			{
				if (slot[0].id == tiid)
				{
					AddInv(0, tiid, tia, 0, 0);
					slot[tmpi].Reset();
				}
				else if (slot[tmpi].size() == 2)
				{
					Unequip(0);
					if (slot[1].id)
					{
						Unequip(1);
					}
					SwapInv(0, tmpi);
				}
				else if (!slot[1].id)
				{
					if (slot[0].size() == 2)
					{
						SwapInv(0, tmpi);
					}
					else if (slot[0].IsArm() && slot[tmpi].IsArm())
					{
						Unequip(0);
						SwapInv(0, tmpi);
					}
					else
					{
						SwapInv(1, tmpi);
					}
				}
				else if (slot[1].IsArm())
				{
					Unequip(1);
					SwapInv(1, tmpi);
				}
				else if (slot[0].IsArm())
				{
					Unequip(0);
					SwapInv(0, tmpi);
				}
				else
				{
					CmdInit();
					printw("Which one would you like to switch?\n");
					prtsinv(0);
					printw("\n");
					prtsinv(1);
					printw("\n0.cancel\n");
					refresh();
					int ipt = InputNum(2);
					if (!ipt)
					{
						return;
					}
					SwapInv(ipt - 1, tmpi);
				}
			}
			msg.print("You grabbed %s x%d in your hand.", GetItemNm(tiid), tia);
			break;
		case 5:
			{
				int tmpta = 0;
				if (tia > 1)
				{
					CmdInit();
					printw("Enter amount, or 0 to cancel(total %d).\n", tia);
					tmpta = InputNum(tia);
					if (tmpta == 0)
					{
						return;
					}
				}
				else
				{
					tmpta = tia;
				}
				msg.print("You've thrown %s x%d away.", GetItemNm(tiid), tmpta);
				AddItem(tiid, tmpta, slot[tmpi].lvl, slot[tmpi].mod, 0, p);
				slot[tmpi].Adj(-tmpta);
				break;
			}
		case 6:
			{
				int tpi = 0, tpid = 0;
				prtinv();
				while (1)
				{
					CmdInit();
					printw("Enter number to select object,0 to exit.\n");
					refresh();
					tpi = InputNum(30);
					if (tpi == 0)
					{
						return;
					}
					tpi--;
					if (tpi == tmpi)
					{
						msg.print("cannot adapt self.");
						continue;
					}
					tpid = slot[tpi].id;
					if (!tpid)
					{
						msg.print("You've select nothing.");
						continue;
					}
					break;
				}
				if (!slot[tmpi].Adapt(tpi))
				{
					continue;
				}
				msg.print("adapted.");
				break;
			}
		case 7:
			{
				int no = 1;
				CmdInit();
				printw("1.all\n");
				for (int i = 1; i < pnum; i++)
				{
					if (slot[tmpi].pid[i])
					{
						printw("%d.%d x%d\n", ++no, slot[tmpi].pid[i],
							   slot[tmpi].pamt[i]);
					}
				}
				printw("0.exit\n");
				refresh();
				int ipt = InputNum(no);
				switch (ipt)
				{
				case 0:
					return;
				case 1:
					if (!slot[tmpi].Decrafta())
					{
						continue;
					}
					break;
				default:
					if (!slot[tmpi].Decraft(no - 1))
					{
						continue;
					}
				}
				break;
			}
		}
		tm.Adj(4, 0, 0);
		Refresh();
		if (health <= 0)
		{
			return;
		}
		if (slot[tmpi].id != tiid)
		{
			goto loop1;
		}
	}
}

void CPlayer::Qhlth()
{
	if (health == maxhlth)
	{
		msg.print("You don't need any food.");
		return;
	}
	for (int i = 0; i < 30; i++)
	{
		if (slot[i].type() == 1)
		{
			int tid = slot[i].id;
			Adjhlth(GetItemFd(tid), 3, tid);
			slot[i].Adj(-1);
			tm.Adj(4, 0, 0);
			Refresh();
			return;
		}
	}
	msg.print("there's nothing to eat.");
}

void CPlayer::Qmana()
{
	if (mp == mxmp)
	{
		msg.print("You don't need any food.");
		return;
	}
	for (int i = 0; i < 30; i++)
	{
		if (slot[i].type() == 11)
		{
			int tid = slot[i].id;
			Adjmana(GetItemFm(tid), 3, tid);
			slot[i].Adj(-1);
			tm.Adj(4, 0, 0);
			Refresh();
			return;
		}
	}
	msg.print("there's nothing to eat.");
}

int CPlayer::IsGrab(int nid)
{
	for (int i = 0; i < 2; i++)
	{
		if (slot[i].id == nid)
		{
			return 1;
		}
	}
	return 0;
}

int CPlayer::IsEquipped(int nid)
{
	for (int i = 2; i < 10; i++)
	{
		if (slot[i].id == nid)
		{
			return 1;
		}
	}
	return 0;
}

int CPlayer::GetAtk(int n)
{
	int matk = 2, ratk = 2, wid = slot[n].GetCPid(), watk = GetItemDmg(wid);
	for (int i = 1; i < pnum; i++)
	{
		int tp = slot[n].pid[i];
		if (!tp)
		{
			break;
		}
		switch (tp)
		{
		case 31:
			watk += 5;
			break;
		}
	}
	switch (slot[n].type())
	{
	case 9:
		{
			int atype = GetAmmoType(wid);
			if (!GetInvAmt(atype))
			{
				msg.print(15,"Out of ammo.");
				return 0;
			}
			return ratk + watk + GetItemAdmg(atype);
		}
	case 10:
		if (mp >= GetMpc(wid))
		{
			return watk;
		}
		msg.print(15,"Out of mana");
		return 0;
	}
	return matk + watk;
}

int CPlayer::GetMpc(int wid)
{
	int cmp = GetItemMpc(wid);
	return cmp;
}

int CPlayer::GetDef()
{
	int tdef = 0;
	for (int i = 2; i < 6; i++)
	{
		tdef += GetItemDef(slot[i].GetCPid());
	}
	return tdef;
}

int CPlayer::GetRng()
{
	int trng = 2;
	for (int i = 0; i < 2; i++)
	{
		int t1 = GetItemRng(slot[i].GetCPid());
		if (GetAtk(i) && t1 > trng)
		{
			trng = t1;
		}
	}
	return trng;
}

int CPlayer::GetSrng()
{
	double t1 = 0;
	int cid = blk[p.geti()];
	switch (cid)
	{
	case 11:
	case 12:
	case 14:
		return 16;
	}
	if (IsGrab(20))
	{
		t1 += 10;
	}
	switch (cid)
	{
	case 0:
	case 1:
	case 3:
	case 5:
	case 6:
	case 7:
	case 10:
	case 15:
		t1 += 36;
		break;
	case 2:
	case 4:
	case 8:
		t1 += 25;
		break;
	default:
		t1 += 16;
		break;
	}
	if (world.IsEvent(4))
	{
		t1 *= 0.8;
	}
	double f = 0.1 + 0.075 * (12 - abs(12 - tm.h));
	t1 *= f;
	return t1 + 1;
}

int CPlayer::GetSpd()
{
	int spd = 1;
	if (isrun)
	{
		spd *= 2;
	}
	return spd;
}

int CPlayer::GetCc(int n)
{
	int bcc = 0;
	switch (slot[n].type())
	{
	case 8:
		bcc = 5;
		break;
	case 9:
		bcc = 5;
		break;
	}
	return bcc + GetItemCc(slot[n].GetCPid());
}

int CPlayer::GetAtt()
{
	int att = 0, batt = 0, t1 = 0;
	for (int i = 0; i < 2; i++)
	{
		t1 = GetItemAtt(slot[i].GetCPid());
		if (t1 > att)
		{
			att = t1;
		}
	}
	return batt + att;
}

int CPlayer::Adjmana(int n, int evt, int obj)
{
	int t = mp + n;
	prtadjm(n, -1, evt, obj);
	if (t < 0)
	{
		return 0;
	}
	else if ((mp = t) > mxmp)
	{
		mp = mxmp;
	}
	return 1;
}

void CPlayer::AddExp(int aexp)
{
	int tlmt = 0;
	exp += aexp;
	msg.print("You gained %d exp points.", aexp);
	while (1)
	{
		tlmt = 30 * (1 + 0.5 * lvl * lvl);
		if (exp < tlmt)
		{
			break;
		}
		exp -= tlmt;
		lvl++;
		msg.print("Level up!");
		msg.SetAttr(11);
		maxhlth = 100 + 10 * lvl;
		health = maxhlth;
		mxmp = 20 + 10 * lvl;
		mp = mxmp;
	}
}

void CPlayer::Reset()
{
	Wipebuff();
	p.Reset();
	spn.Reset();
	id = -1;
	health = maxhlth = 100;
	lvl = 0;
	exp = 0;
	isrun = 0;
	mp = mxmp = 20;
	ptgt = 0;
	for (int i = 0; i < 30; i++)
	{
		slot[i].Reset();
	}
}

void CPlayer::Respawn()
{
	Wipebuff();
	p = spn;
	health = 0.8 * maxhlth;
	isrun = 0;
	ptgt = 0;
}

void CPlayer::Sleep()
{
	int hme = 0;
	if (tm.IsNt())
	{
		for (int i = 0; i < 100; i++)
		{
			if (world.witem[i].id == 26 && world.witem[i].plc && world.witem[i].p == p)
			{
				hme = 1;
				break;
			}
		}
		if (hme)
		{
			msg.print("You lay down and fell asleep...");
			msg.Show();
			refresh();
			sleep(2);
			spn = p;
			health = maxhlth;
			mp = mxmp;
			if (tm.h < 24)
			{
				tm.d++;
			}
			tm.h = 6;
			tm.m = 0;
			tm.Exchg();
			msg.print("You were woken up by the morning light.");
			Refresh();
			return;
		}
		else
		{
			msg.print("You can't sleep in the wild.");
		}
	}
	else
	{
		msg.print("Stop daydreaming.");
	}
}

void CPlayer::Unequip(int n)
{
	for (int i = 10; i < 30; i++)
	{
		if (!slot[i].id)
		{
			SwapInv(i, n);
			return;
		}
	}
}

void CPlayer::AddInv(int stn, int nid, int namt, int nlvl, int nmod)
{
	if (!namt)
	{
		return;
	}
	int toamt = namt;
	int mxstk = GetItemMxstk(nid);
	for (int i = stn; i < 30; i++)
	{
		if (i == 2)
		{
			i += 8;
		}
		if (slot[i].id == nid)
		{
			int tamt = mxstk - slot[i].amt;
			int t = min(tamt, namt);
			slot[i].amt += t;
			namt -= t;
			if (namt <= 0)
			{
				goto ext;
			}
		}
	}
	for (int i = stn; i < 30; i++)
	{
		if (i == 2)
		{
			i += 8;
		}
		if (!slot[i].id || slot[i].id == nid)
		{
			int tamt = mxstk - slot[i].amt;
			if (!tamt)
			{
				continue;
			}
			slot[i].Set(nid, 0, nlvl, nmod);
			int t = min(tamt, namt);
			slot[i].amt += t;
			namt -= t;
			if (namt <= 0)
			{
				goto ext;
			}
		}
	}
	if (toamt == namt)
	{
		msg.print("You can take no more thing, dropped %s x%d.", GetItemNm(nid),
			   namt);
	}
	else
	{
		msg.print("You can only take %s x%d, dropped %d.", GetItemNm(nid),
			   toamt - namt, namt);
	}
	AddItem(nid, namt, nlvl, nmod, 0, p);
	return;
  ext:
	msg.print("You've got %s x%d.", GetItemNm(nid), toamt);
}

void CPlayer::AddInv(int nid, int namt, int nlvl, int nmod)
{
	if (!namt)
	{
		return;
	}
	int toamt = namt;
	int mxstk = GetItemMxstk(nid);
	for (int i = 10; i < 30; i++)
	{
		if (slot[i].id == nid)
		{
			int tamt = mxstk - slot[i].amt;
			int t = min(tamt, namt);
			slot[i].amt += t;
			namt -= t;
			if (namt <= 0)
			{
				goto ext;
			}
		}
	}
	for (int i = 10; i < 30; i++)
	{
		if (!slot[i].id || slot[i].id == nid)
		{
			int tamt = mxstk - slot[i].amt;
			if (!tamt)
			{
				continue;
			}
			slot[i].Set(nid, 0, nlvl, nmod);
			int t = min(tamt, namt);
			slot[i].amt += t;
			namt -= t;
			if (namt <= 0)
			{
				goto ext;
			}
		}
	}
	if (toamt == namt)
	{
		msg.print("You can take no more thing, dropped %s x%d.", GetItemNm(nid),
			   namt);
	}
	else
	{
		msg.print("You can only take %s x%d, dropped %d.", GetItemNm(nid),
			   toamt - namt, namt);
	}
	AddItem(nid, namt, nlvl, nmod, 0, p);
	return;
  ext:
	msg.print("You've got %s x%d.", GetItemNm(nid), toamt);
}

void CPlayer::DecInv(int nid, int namt)
{
	for (int i = 0; i < 30; i++)
	{
		if (!namt)
		{
			break;
		}
		if (slot[i].id == nid)
		{
			slot[i].amt -= namt;
			if (slot[i].amt <= 0)
			{
				namt = -slot[i].amt;
				slot[i].Reset();
				continue;
			}
			break;
		}
	}
}

void CPlayer::SwapInv(int n1, int n2)
{
	inv titem = slot[n1];
	slot[n1] = slot[n2];
	slot[n2] = titem;
}

int CPlayer::GetInvAmt(int nid)
{
	int tol = 0;
	for (int i = 0; i < 30; i++)
	{
		if (slot[i].id == nid)
		{
			tol += slot[i].amt;
		}
	}
	return tol;
}

void CPlayer::Move(int n)
{
	int plspd = GetSpd(), mv = 0;
	while (plspd > 0)
	{
		if (IsCollp(n))
		{
			msg.print("blocked");
			break;
		}
		p.move(n, 1);
		mv = 1;
		plspd--;
	}
	if (mv)
	{
		tm.Adj(4, 0, 0);
		fbio = GetBiome(p);
		SetSpnEnv();
		if (mp < mxmp && --pml == 0)
		{
			Adjmana(1, 0, 0);
			pml = 2 + isrun;
		}
		if (health < maxhlth && --phl == 0)
		{
			Adjhlth(1, 0, 0);
			phl = 3 + isrun;
		}
		Refresh();
	}
}

void SetPlpos()
{
	int rx = 0, ry = 0;
	int tmp = 0;
	while (1)
	{
		rx = randr(700, 1400);
		ry = randr(700, 1400);
		tmp = blk[blki(rx, ry)];
		if (!BlcSlctp(tmp))
		{
			player.p.x = world.wspn.x = player.spn.x = rx;
			player.p.y = world.wspn.y = player.spn.y = ry;
			break;
		}
	}
	msg.print(13, "You woke up in the %s.", GetBlkNm(tmp));
}
