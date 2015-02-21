#include "main.h"
using namespace std;
int scr_w, scr_h;
attr_t attr[17];
// attr list 
// 0 white(default) 
// 1 black 
// 2 red 
// 3 green 
// 4 yellow 
// 5 blue 
// 6 purple 
// 7 cyan 
// 8 bold_white 
// 9 grey 
// 10 b_red 
// 11 b_green 
// 12 b_yellow 
// 13 b_blue 
// 14 b_purple 
// 15 b_cyan
// 16 reserved

int mx(int w)
{
	return (scr_w - w) / 2;
}

int my(int h)
{
	return (scr_h - h) / 2;
}

int mx(int w, int cw)
{
	return (cw - w) / 2;
}

int my(int h, int ch)
{
	return (ch - h) / 2;
}

int cx()
{
	int tx, ty;
	getyx(stdscr, ty, tx);
	return tx;
}

int cy()
{
	int tx, ty;
	getyx(stdscr, ty, tx);
	return ty;
}

void printwr(const char *ch, ...)
{
	va_list arg;
	va_start(arg, ch);
	vwprintw(stdscr, ch, arg);
	va_end(arg);
	refresh();
}

void printwr(int attn, const char *ch, ...)
{
	va_list arg;
	va_start(arg, ch);
	attron(attr[attn]);
	vwprintw(stdscr, ch, arg);
	attroff(attr[attn]);
	va_end(arg);
	refresh();
}

void initattr()
{
	for (int c = 0; c < 8; c++)
	{
		init_pair(c + 1, c, COLOR_BLACK);
	}
	int p = 0;
	for (int j = 0; j < 8; j++)
	{
		attr[p++] = COLOR_PAIR(j);
	}
	for (int j = 0; j < 8; j++)
	{
		attr[p++] = COLOR_PAIR(j) | A_BOLD;
	}
}

void prtbuff(int bid, int sbj, int obj)
{
	const char *sbjn = "You", *objn = "You";
	if (sbj > 0 && sbj < mobn)
	{
		sbjn = GetMobNm(sbj);
	}
	if (!obj)
	{
		msg.print("%s got inflicted with %s buff.", sbjn, GetBuffNm(bid));
		goto attrset;
	}
	else if (obj > 0)
	{
		objn = GetMobNm(obj);
	}
	msg.print("%s inflict %s buff on %s.", objn, GetBuffNm(bid), sbjn);
  attrset:
	if (sbj == -1)
	{
		msg.SetAttr(15);
	}
}

void prtadjm(int n, int sbj, int evt, int obj)
{
	const char *sbjn = "You", *objn = "You";
	if (sbj > 0)
	{
		sbjn = GetMobNm(sbj);
	}
	switch (evt)
	{
	case 1:
		if (obj > 0)
		{
			objn = GetMobNm(obj);
		}
		msg.print("%s hit %s", objn, sbjn);
		break;
	case 3:
		objn = GetItemNm(obj);
		switch (GetItemType(obj))
		{
		case 11:
			msg.print("%s consumed a %s", sbjn, objn);
			break;
		case 9:
			msg.print("%s got bombed by %s", sbjn, objn);
			break;
		default:
			msg.print("%s got mysteriously affected by %s", sbjn, objn);
		}
		break;
	case 4:
		switch (obj)
		{
		case 1:
			msg.print("%s got shocked by the lightning", sbjn);
			break;
		}
		break;
	default:
		return;
	}
	msg.add(", mana %+d.", n);
}

void prtadjh(int n, int sbj, int evt, int obj)
{
	const char *sbjn = "You", *objn = "You";
	if (sbj > 0)
	{
		sbjn = GetMobNm(sbj);
	}
	switch (evt)
	{
	case 1:
		if (obj > 0)
		{
			objn = GetMobNm(obj);
		}
		msg.print("%s hit %s", objn, sbjn);
		break;
	case 3:
		objn = GetItemNm(obj);
		switch (GetItemType(obj))
		{
		case 1:
			msg.print("%s consumed a %s", sbjn, objn);
			break;
		case 9:
			msg.print("%s got bombed by %s", sbjn, objn);
			break;
		default:
			msg.print("%s got blah blah by %s", sbjn, objn);
		}
		break;
	case 4:
		switch (obj)
		{
		case 1:
			msg.print("%s got shocked by the lightning", sbjn);
			break;
		}
		break;
	default:
		return;
	}
	msg.add(", health %+d.", n);
}

void prtdmsg(int sbj, int evt, int obj)
{
	const char *sbjn = "You", *objn = "You";
	if (sbj > 0)
	{
		sbjn = GetMobNm(sbj);
	}
	switch (evt)
	{
	case 1:
		if (obj > 0)
		{
			objn = GetMobNm(obj);
		}
		if (sbj < 0)
		{
			msg.print("%s were slain by %s.", sbjn, objn);
		}
		else
		{
			msg.print("%s killed %s.", objn, sbjn);
		}
		break;
	case 2:
		switch (obj)
		{
		case 1:
			msg.print("%s was burned down.", sbjn);
			break;
		case 3:
			msg.print("%s didn't find the antidote.", sbjn);
			break;
		}
		break;
	case 3:
		objn = GetItemNm(obj);
		switch (GetItemType(obj))
		{
		case 1:
			msg.print("%s consumed a %s and died.", sbjn, objn);
			break;
		case 9:
			msg.print("%s was blown up.", sbjn);
			break;
		default:
			msg.print("%s blahly died because of %s.", sbjn, objn);
		}
	case 4:
		switch (obj)
		{
		case 1:
			msg.print("%s got fried.", sbjn);
			break;
		}
		break;
	}
	if (sbj == -1)
	{
		msg.SetAttr(10);
	}
}

void prtbar(int val, int max)
{
	for (int i = 0; i < max / 5; i++)
	{
		if (val > 5 * i)
		{
			printw("|");
			continue;
		}
		printw(".");
	}
	printw("\n");
}

int GetBuffCol(int id)
{
	switch (id)
	{
	case 1:
		return 10;
	case 2:
		return 11;
	case 3:
		return 14;
	}
	return 0;
}

const char GetBuffChar(int id)
{
	switch (id)
	{
	case 1:
		return 'F';
	case 2:
		return '+';
	case 3:
		return 'P';
	}
	return 'B';
}

void prtmain()
{
	int tx = mx(12), ty = scr_h * 0.3;
	clear();
	mvprintw(0, 0, "width %d, height %d", scr_w, scr_h);
	attron(A_BOLD);
	mvprintw(ty, tx, "Project Junk");
	attroff(A_BOLD);
	mvprintw(++ty, tx, "1.Start");
	mvprintw(++ty, tx, "2.Continue");
	mvprintw(++ty, tx, "0.Exit");
	move(ty + 1, tx);
	refresh();
}

void prtpldth()
{
	int tx = mx(8), ty = scr_h * 0.3;
	clear();
	attron(attr[10]);
	mvprintw(ty, tx, "You Died");
	attroff(attr[10]);
	mvprintw(++ty, mx(20), "1.Respawn");
	mvprintw(ty, cx() + 4, "0.Exit");
	move(ty + 1, tx);
	refresh();
}

void prtile(char c, int attn)
{
	attron(attr[attn]);
	printw("%c ", c);
	attroff(attr[attn]);
}

void prthud()
{
	refresh();
	clear();
	printw("Health:%d/%d", player.health, player.maxhlth);
	move(1, 0);
	prtbar(player.health, player.maxhlth);
	printw("Mana:%d/%d", player.mp, player.mxmp);
	move(3, 0);
	prtbar(player.mp, player.mxmp);
	mvprintw(0, scr_w - 5, "Buffs");
	move(1, scr_w - 2);
	for (int i = 0; i < 10; i++)
	{
		int bid = player.buff[i].id;
		if (bid)
		{
			prtile(GetBuffChar(bid), GetBuffCol(bid));
			move(1, scr_w - (i + 2) * 2);
		}
	}
	move(3, scr_w - 20);
	for (int i = 0; i < 2; i++)
	{
		if (player.slot[i].type() == 9)
		{
			printw("Ammo:%d", player.GetInvAmt(GetAmmoType(player.slot[i].GetCPid())));
			break;
		}
	}
	move(my(13, scr_h - 4 - msgh - comh), mx(26));
#if devmode
	player.IsEquipped(32) ? prtfmp(8) : prtmp(6);
#else
	prtmp(6);
#endif
	int p = player.ptgt;
	if (p)
	{
		mvprintw(scr_h - msgh - comh - 1, 0, "Target: %s (%d/%d)\n", mob[p - 1].name(),
				 mob[p - 1].health, mob[p - 1].maxhlth);
		prtbar(mob[p - 1].health, mob[p - 1].maxhlth);
	}
	msg.Init(ctop(0, scr_h - msgh), ctop(scr_w - 1, scr_h - 1));
	msg.Show();
	refresh();
}

void prtast()
{
	if (tm.h < 5)
	{
		msg.print("You see stars in the sky.");
	}
	else if (tm.h < 6)
	{
		msg.print("The sky is getting brighter.");
	}
	else if (tm.h < 12)
	{
		msg.print("It's morning.");
	}
	else if (tm.h < 17)
	{
		msg.print("It's afternoon.");
	}
	else if (tm.h < 18)
	{
		msg.print("You saw the twilight falling.");
	}
	else if (tm.h < 24)
	{
		msg.print("You are covered in moon light.");
	}
}

void Obsrv()
{
	int mfnd = 0, plsrng = player.GetSrng();
	unsigned long dist;
	msg.print("You are now in the %s.", GetBlkNm(blk[player.p.geti()]));
	msg.print("(debug)time %d:%d day %d pos: %d,%d", tm.h, tm.m, tm.d, player.p.x, player.p.y);
	prtast();
	for (int i = 0; i < inum; i++)
	{
		if (witem[i].id && witem[i].p + player.p <= plsrng && !IsColls(witem[i].p, player.p))
		{
			if (witem[i].plc)
			{
				msg.print("You saw a %s on your %s.",
						  GetItemNm(witem[i].id), GetDirNm(GetDir(player.p, witem[i].p)));
			}
			else
			{
				msg.print("You saw %s x%d dropped on your %s.",
						  GetItemNm(witem[i].id), witem[i].amt,
						  GetDirNm(GetDir(player.p, witem[i].p)));
			}
		}
	}
	for (int i = 0; i < mobn; i++)
	{
		if (mob[i].id && (dist = player.p + mob[i].p) <= plsrng && !IsColls(player.p, mob[i].p))
		{
			msg.print("You saw a %s(%d/%d) on your %s.", mob[i].name(),
					  mob[i].health, mob[i].maxhlth, GetDirNm(GetDir(player.p, mob[i].p)));
			mfnd = 1;
		}
	}
	if (!mfnd)
	{
		msg.print("You saw nobody.");
	}
	else
	{
		mfnd = 0;
	}
}

int prtmb(int rng)
{
	move(scr_h - msgh - comh, 0);
	int no = 0, cnum[mobn];
	for (int i = 0; i < mobn; i++)
	{
		if (mob[i].id && (!rng || player.p + mob[i].p <= rng && !IsColls(player.p, mob[i].p)))
		{
			cnum[no++] = i;
		}
	}
	if (!no)
	{
		return -1;
	}
	if (no == 1)
	{
		return cnum[0];
	}
	for (int j = 0; j < no; j++)
	{
		int i = cnum[j];
		printw("%d. %s lv.%d (%d/%d)", j + 1, mob[i].name(), mob[i].lvl, mob[i].health,
			   mob[i].maxhlth);
		if (j % 2)
		{
			printw("\n");
		}
		else
		{
			move(cy(), 30);
		}
	}
	if (no % 2)
	{
		printw("\n");
	}
	mvprintw(scr_h - msgh - 2, 0, "Enter number to select, 0 to cancel.\n");
	refresh();
	int tmp = InputNum(no);
	if (tmp == 0)
	{
		return -2;
	}
	return cnum[tmp - 1];
}

int GetBlkCol(int id)
{
	switch (id)
	{
	case 0:
		return 9;
	case 1:
		return 11;
	case 2:
		return 3;
	case 3:
		return 13;
	case 4:
		return 15;
	case 5:
		return 10;
	case 6:
		return 14;
	case 7:
		return 12;
	case 8:
		return 3;
	case 9:
		return 11;
	case 10:
		return 3;
	case 11:
		return 5;
	case 12:
		return 4;
	case 13:
		return 12;
	case 14:
		return 7;
	case 15:
		return 9;
	case 16:
		return 2;
	default:
		return 0;
	}
}

const char GetBlkChar(int id)
{
	switch (id)
	{
	case 0:
		return 'd';
	case 1:
		return 'g';
	case 2:
		return 'f';
	case 3:
		return '~';
	case 4:
		return '_';
	case 5:
		return 'm';
	case 6:
		return '^';
	case 7:
		return 's';
	case 8:
		return 'j';
	case 9:
		return 'b';
	case 10:
		return 'S';
	case 11:
		return '#';
	case 12:
		return '*';
	case 13:
		return '[';
	case 14:
		return '-';
	case 15:
		return '|';
	case 16:
		return '=';
	default:
		return '?';
	}
}

int GetMobCol(int id)
{
	switch (id)
	{
	case -1:
		return 0;
	case 1:
		return 9;
	case 2:
		return 12;
	case 3:
		return 5;
	case 4:
		return 11;
	case 5:
		return 9;
	case 6:
		return 9;
	case 8:
		return 6;
	case 9:
		return 6;
	case 10:
		return 9;
	case 11:
		return 0;
	case 12:
		return 2;
	case 13:
		return 0;
	case 14:
		return 0;
	case 15:
	case 16:
	case 17:
		return 4;
	case 18:
		return 0;
	case 19:
		return 10;
	case 20:
		return 0;
	default:
		return 0;
	}
}

const char GetMobChar(int id)
{
	switch (id)
	{
	case -1:
		return 'P';
	case 1:
		return 'h';
	case 2:
		return 'c';
	case 3:
		return 'F';
	case 4:
		return 'V';
	case 5:
		return 'W';
	case 6:
		return 'B';
	case 8:
		return '+';
	case 9:
		return 'M';
	case 10:
		return '&';
	case 11:
		return 'D';
	case 12:
		return 'Z';
	case 13:
		return '@';
	case 14:
		return 'H';
	case 15:
	case 16:
	case 17:
		return 'C';
	case 18:
		return 'Q';
	case 19:
		return 'R';
	case 20:
		return 'A';
	default:
		return 'O';
	}
}

int GetItemCol(int id)
{
	switch (id)
	{
	case 24:
		return 0;
	case 25:
		return 12;
	case 26:
		return 0;
	default:
		return 9;
	}
}

const char GetItemChar(int id)
{
	switch (id)
	{
	case 24:
		return 'T';
	case 25:
		return 'X';
	case 26:
		return '^';
	default:
		return 'i';
	}
}

void prthmp()
{
	clear();
	int wid = scr_w / 2 - 1;
	int chs = wlth / wid, chc[blkid + 1];
	pos cp;
	for (cp.y = 0; cp.y <= wlth - chs; cp.y += chs)
	{
		for (cp.x = 0; cp.x <= wlth - chs; cp.x += chs)
		{
			for (int i = 0; i <= blkid; i++)
			{
				chc[i] = 0;
			}
			for (int cx = cp.x; cx < cp.x + chs; cx++)
			{
				for (int cy = cp.y; cy < cp.y + chs; cy++)
				{
					chc[blk[blki(cx, cy)]]++;
				}
			}
			int maxb = 0;
			for (int i = 1; i <= blkid; i++)
			{
				if (chc[maxb] < chc[i])
				{
					maxb = i;
				}
			}
			prtile(GetBlkChar(maxb), GetBlkCol(maxb));
		}
		printw("\n");
	}
	refresh();
}

void prtfmp(int rng)
{
	clear();
	int mf = 0, fi = 0;
	for (int cy = player.p.y - rng; cy <= player.p.y + rng; cy++)
	{
		for (int cx = player.p.x - rng; cx <= player.p.x + rng; cx++)
		{
			if (player.p == ctop(cx, cy))
			{
				prtile(GetMobChar(-1), GetMobCol(-1));
				continue;
			}
			for (int i = 0; i < inum; i++)
			{
				if (witem[i].id && witem[i].p == ctop(cx, cy) && witem[i].plc)
				{
					prtile(GetItemChar(witem[i].id), GetItemCol(witem[i].id));
					fi = 1;
					break;
				}
			}
			if (fi)
			{
				fi = 0;
				continue;
			}
			for (int j = 0; j < mobn; j++)
			{
				if (mob[j].id && mob[j].p == ctop(cx, cy))
				{
					prtile(GetMobChar(mob[j].id), GetMobCol(mob[j].id));
					mf = 1;
					break;
				}
			}
			if (mf)
			{
				mf = 0;
				continue;
			}
			prtile(GetBlkChar(blk[blki(cx, cy)]), GetBlkCol(blk[blki(cx, cy)]));
		}
		printw("\n");
	}
	refresh();
}

void prtmp(int rng)
{
	int mf = 0, fi = 0, plsrng = player.GetSrng(), tmx = cx();
	for (int ty = player.p.y - rng; ty <= player.p.y + rng; ty++)
	{
		for (int tx = player.p.x - rng; tx <= player.p.x + rng; tx++)
		{
			if (player.p == ctop(tx, ty))
			{
				prtile(GetMobChar(-1), GetMobCol(-1));
				continue;
			}
			for (int i = 0; i < inum; i++)
			{
				if (witem[i].id && witem[i].p == ctop(tx, ty)
					&& witem[i].p + player.p <= plsrng
					&& !IsColls(witem[i].p, player.p) && witem[i].plc)
				{
					prtile(GetItemChar(witem[i].id), GetItemCol(witem[i].id));
					fi = 1;
					break;
				}
			}
			if (fi)
			{
				fi = 0;
				continue;
			}
			for (int j = 0; j < mobn; j++)
			{
				if (mob[j].id && mob[j].p == ctop(tx, ty)
					&& mob[j].p + player.p <=
					plsrng + mob[j].GetAtt() && !IsColls(player.p, mob[j].p))
				{
					prtile(GetMobChar(mob[j].id), GetMobCol(mob[j].id));
					mf = 1;
					break;
				}
			}
			if (mf)
			{
				mf = 0;
				continue;
			}
			if (ctop(tx, ty) + player.p > plsrng || IsCollb(player.p, ctop(tx, ty)))
			{
				printw("  ");
				continue;
			}
			if (tx < 0 || tx > wlth - 1 || ty < 0 || ty > wlth - 1)
			{
				continue;
			}
			prtile(GetBlkChar(blk[blki(tx, ty)]), GetBlkCol(blk[blki(tx, ty)]));
		}
		move(cy() + 1, tmx);
	}
}

void prtime()
{
	msg.print("Showing the time\nDay %d Year %d\nTime:%d:%02d", tm.d, tm.d / 360, tm.h, tm.m);
}

void prtsinv(int n)
{
	printw("%02d.", n + 1);
	if (player.slot[n].id)
	{
		printw("%s x%3d", GetItemNm(player.slot[n].id), player.slot[n].amt);
	}
	else
	{
		printw("---");
	}
}

void prtinv()
{
	printw("Inventory\nLeft hand");
	mvprintw(cy(), scr_w - 10, "Right hand");
	prtsinv(0);
	move(cy(), 0.6 * scr_w);
	prtsinv(1);
	mvprintw(cy() + 1, 0, "Wearings");
	mvprintw(cy(), scr_w - 11, "Accessories");
	for (int i = 2; i < 6; i++)
	{
		switch (i)
		{
		case 2:
			printw("head:");
			break;
		case 3:
			printw("body:");
			break;
		case 4:
			printw("legs:");
			break;
		case 5:
			printw("feet:");
			break;
		}
		prtsinv(i);
		move(cy(), 0.6 * scr_w);
		prtsinv(i + 4);
		printw("\n");
	}
	printw("Items\n");
	for (int i = 10; i < 30; i++)
	{
		move(cy(), scr_w * 0.3 * ((i - 1) % 3));
		prtsinv(i);
		if (!(i % 3))
		{
			printw("\n");
		}
	}
	printw("\n");
	msg.Init(ctop(0, scr_h - msgh), ctop(scr_w - 1, scr_h - 1));
	msg.Show();
}

void prtcrash()
{
	abort();
}

void prtwst()
{
	clear();
	double n[17];
	for (int i = 0; i < 17; i++)
	{
		n[i] = 0;
	}
	for (int i = 0; i < wlth * wlth; i++)
	{
		n[blk[i]]++;
	}
	for (int i = 0; i < 17; i++)
	{
		printw("%s: %.2f\n", GetBlkNm(i), 100 * n[i] / (wlth * wlth));
	}
	refresh();
}

void prtst()
{
	clear();
	printw
		("Showing %s's stat\npos: x:%ld y:%ld\nhealth:%d/%d\nlevel:%d exp:%d\natk:%d\ndef:%d\nrng:%d\nsrng:%d\n",
		 player.name, player.p.x, player.p.y, player.health,
		 player.maxhlth, player.lvl, player.exp, player.GetAtk(0),
		 player.GetDef(), player.GetRng(), player.GetSrng());
	refresh();
}

void prtmst(int n)
{
	printw
		("Showing mob #%d's stat\nste:%d tgt:%d lst:%d\nName:%s\nid:%d\nHealth:%d/%d\nAtk:%d\nDef:%d\nRange:%d\nSrange:%d\nlvl:%d\npos: x:%ld y:%ld\n",
		 n, mob[n].ste, mob[n].tgt, mob[n].lst, mob[n].name(),
		 mob[n].id, mob[n].health, mob[n].maxhlth,
		 mob[n].GetMatk(), mob[n].GetDef(), mob[n].GetRng(),
		 mob[n].GetSrng(), mob[n].lvl, mob[n].p.x, mob[n].p.y);
}