#include "main.h"
#define GDIR "./Game"
#define PDIR GDIR"/Players"
#define WDIR GDIR"/Worlds"
using namespace std;
int GameStart()
{
	prtmain();
	msg.Init(ctop(0, scr_h - msgh), ctop(scr_w - 1, scr_h - 1));
	CmdInit();
	msg.Show();
	refresh();
	int ipt1 = InputNum(2);
	if (ipt1 == 0)
	{
		return 0;
	}
	else if (ipt1 == 1)
	{
		sprintf(player.name, "Alpha");
		world.Init();
		GenerateW();
		SetPlpos();
		world.InitEvent();
	}
	else if (ipt1 == 2)
	{
		if (!LoadW() || !LoadP())
		{
			return -1;
		}
	}
	SetSpnEnv();
	return 1;
}

int Command()
{
	char input[1024], *tpc;
	mvprintw(scr_h - msgh - 1, 0, ">");
	echo();
	getstr(input);
	noecho();
	tpc = strtok(input, " ");
	if (!tpc)
	{
		return 0;
	}
	if (!strcmp(tpc, "exit"))
	{
		SavW();
		SavP();
		return 1;
	}
	if (!strcmp(tpc, "save"))
	{
		SavW();
		SavP();
	}
	else if (!strcmp(tpc, "ne"))
	{
		player.Move(2);
	}
	else if (!strcmp(tpc, "se"))
	{
		player.Move(4);
	}
	else if (!strcmp(tpc, "sw"))
	{
		player.Move(6);
	}
	else if (!strcmp(tpc, "nw"))
	{
		player.Move(8);
	}
	else if (!strcmp(tpc, "keymap"))
	{
		KeySet();
	}
	else if (!strcmp(tpc, "updscr"))
	{
		getmaxyx(stdscr, scr_h, scr_w);
		msg.print("current scr W*H: %d*%d", scr_w, scr_h);
	}
	else if (!strcmp(tpc, "clrmsg"))
	{
		msg.Clear();
	}
	else if (!strcmp(tpc, "bang"))
	{
		Explode(player.p, 44);
	}
	else if (!strcmp(tpc, "decap"))
	{
		int i = prtmb(0);
		if (i >= 0)
		{
			mob[i].Reset();
		}
	}
	else if (!strcmp(tpc, "watch"))
	{
		int i = prtmb(0);
		if (i >= 0)
		{
			player.ptgt = i + 1;
		}
	}
	else if (!strcmp(tpc, "tp"))
	{
		char *c1 = strtok(NULL, " ");
		if (!strcmp(c1, "random"))
		{
			player.p.x = randr(200, 1800);
			player.p.y = randr(200, 1800);
		}
		else if (!strcmp(c1, "spawn"))
		{
			player.p = player.spn;
		}
		else if (c1)
		{
			int tx = atoi(c1);
			int ty = GetPara();
			player.p.x = tx;
			player.p.y = ty;
		}
		msg.print("You've teleported.");
	}
	else if (!strcmp(tpc, "map"))
	{
		clear();
		prtfmp(player.p, min(scr_h, scr_w / 2) / 2 - 1);
		getch();
	}
	else if (!strcmp(tpc, "hmap"))
	{
		prthmp(min(scr_h, scr_w / 2));
		getch();
	}
	else if (!strcmp(tpc, "nuke"))
	{
		for (int i = 0; i < mobn; i++)
		{
			mob[i].Reset();
		}
		tolspn = 0;
		msg.print("Boom!\nEvery mob was wiped out...(I wonder why you're still around...)");
	}
	else if (!strcmp(tpc, "spnchk"))
	{
		msg.print("result %d", SpawnChk(GetPara(), blk[player.p.geti()]));
	}
	else if (!strcmp(tpc, "spawn"))
	{
		int tid = GetPara();
		int tx = GetPara();
		int ty = GetPara();
		char *tc = strtok(NULL, " ");
		int amt;
		if (!tc)
		{
			amt = 1;
		}
		else
		{
			amt = atoi(tc);
		}
		tx += player.p.x;
		ty += player.p.y;
		for (int i = 0; i < mobn; i++)
		{
			if (!mob[i].id)
			{
				mob[i].Spawn(tid, i + 1, ctop(tx, ty));
				amt--;
				if (!amt)
				{
					break;
				}
			}
		}
	}
	else if (!strcmp(tpc, "time"))
	{
		prtime();
	}
	else if (!strcmp(tpc, "j"))
	{
		int nh = GetPara();
		int nm = GetPara();
		int nd = GetPara();
		if (nh || nm || nd)
		{
			tm.Adj(nm, nh, nd);
		}
	}
	else if (!strcmp(tpc, "stat"))
	{
		prtst();
		getch();
	}
	else if (!strcmp(tpc, "wstat"))
	{
		prtwst();
		getch();
	}
	else if (!strcmp(tpc, "aid"))
	{
		char *tc = strtok(NULL, " ");
		if (!tc)
		{
			msg.print("Wrong Parameters.");
			return 0;
		}
		if (!strcmp(tc, "full"))
		{
			player.health = player.maxhlth;
			msg.print("You've fully recovered.");
		}
		else
		{
			unsigned int hlth = atoi(tc);
			if (hlth)
			{
				msg.print("You've got %d health.", hlth);
				player.Adjhlth(hlth, 0, 0);
			}
		}
	}
	else if (!strcmp(tpc, "give"))
	{
		unsigned int tid = GetPara();
		unsigned int ta = GetPara();
		if (tid > 0 && ta > 0)
		{
			player.AddInv(tid, ta, 0, 0);
		}
	}
	else if (!strcmp(tpc, "slot"))
	{
		unsigned int id = GetPara();
		unsigned int tid = GetPara();
		unsigned int ta = GetPara();
		if (tid > 0 && ta > 0)
		{
			player.slot[id].Set(tid, ta, 0, 0);
		}
	}
	else if (!strcmp(tpc, "blk"))
	{
		unsigned int tid = GetPara();
		blk[player.p.geti()] = tid;
	}
	else if (!strcmp(tpc, "fart"))
	{
		unsigned int rng = GetPara();
		pos cp = player.p;
		for (int y = cp.y - rng; y <= cp.y + rng; y++)
		{
			int oy = cp.y - y;
			oy *= oy;
			int ox = sqrt(rng * rng - oy);
			for (int x = cp.x - ox; x <= cp.x + ox; x++)
			{
				blk[blki(x, y)] = 0;
			}
		}
	}
	else if (!strcmp(tpc, "ville"))
	{
		GenVillage(player.p);
	}
	else if (!strcmp(tpc, "villes"))
	{
		GenVillages(GetPara());
	}
	else if (!strcmp(tpc, "clrblk"))
	{
		ClrBlk(GetPara(), GetPara());
	}
	else if (!strcmp(tpc, "item"))
	{
		unsigned int tid = GetPara();
		unsigned plc = GetPara();
		if (IsBlkPlc(blk[player.p.geti()]) && !IsItemNear(player.p, 1))
		{
			AddItem(tid, 1, 0, 0, plc, player.p);
		}
	}
	else if (!strcmp(tpc, "wipeitem"))
	{
		for (int i = 0; i < inum; i++)
		{
			if (!world.witem[i].plc)
			{
				world.witem[i].Reset();
			}
		}
	}
	else if (!strcmp(tpc, "listitem"))
	{
		clear();
		for (int i = 0; i < inum; i++)
		{
			if (world.witem[i].id)
			{
				printw("%d %s x%d %ld,%ld\n", i,
					   GetItemNm(world.witem[i].id), world.witem[i].amt, world.witem[i].p.x,
					   world.witem[i].p.y);
			}
		}
		refresh();
		getch();
	}
	else if (!strcmp(tpc, "listthing"))
	{
		for (int i = 0; i < itmid; i++)
		{
			clear();
			printwr("%d %s\n", i, GetItemNm(i));
			getch();
		}
	}
	else if (!strcmp(tpc, "listmob"))
	{
		for (int i = 1; i <= mobid; i++)
		{
			clear();
			printwr
				("%s id:%d\nHealth:%d\nAtk(m/r):%d/%d Def:%d\nRng:%d Srng:%d Spd:%d\n\n",
				 GetMobNm(i), i, GetMobMhlth(i), GetMobMatk(i),
				 GetMobRatk(i), GetMobDef(i), GetMobRng(i), GetMobSrng(i), GetMobSpd(i));
			getch();
		}
	}
	else if (!strcmp(tpc, "mstat"))
	{
		clear();
		printw("%d/%d %d\n", tolspn, maxspn, spnrt);
		for (int i = 0; i < mobn; i++)
		{
			if (mob[i].id)
			{
				getch();
				clear();
				prtmst(i);
				refresh();
			}
		}
		refresh();
		getch();
	}
	else if (!strcmp(tpc, "buff"))
	{
		int tgt = GetPara();
		int bid = GetPara();
		int dur = GetPara();
		if (tgt == -1)
		{
			player.Addbuff(bid, dur, 0);
		}
		else if (tgt > 0)
		{
			mob[--tgt].Addbuff(bid, dur, 0);
		}
	}
	else if (!strcmp(tpc, "exp"))
	{
		unsigned int ex = GetPara();
		if (ex)
		{
			player.AddExp(ex);
		}
	}
	else if (!strcmp(tpc, "lvl"))
	{
		unsigned int tl = GetPara();
		if (tl)
		{
			player.lvl += tl;
			player.AddExp(0);
		}
	}
	else if (!strcmp(tpc, "demo"))
	{
		pos cp = ctop(0,0);
		int width = scr_w / 4 - 1;
		while (cp.x < wlth)
		{
			clear();
			cp.x += 1;
			cp.y += 1;
			prtfmp(cp, width);
			usleep(50000);
		}
		cp.x = 0;
		cp.y = wlth - 1;
		while (cp.x < wlth)
		{
			clear();
			cp.x += 1;
			cp.y -= 1;
			prtfmp(cp, width);
			usleep(50000);
		}
	}
	else
	{
		ExceptionProc();
	}
	return 0;
}

void GReset()
{
	fbio = 0;
	tolspn = 0;
	maxspn = 0;
	spnrt = 0;
	for (int i = 0; i < mobn; i++)
	{
		mob[i].Reset();
	}
	world.Reset();
	player.Reset();
	tm.Reset();
	KeyReset();
	CrReset();
	TrReset();
}

int GetPara()
{
	char *tc = strtok(NULL, " ");
	if (!tc)
	{
		msg.print("Wrong Parameters.");
		return 0;
	}
	return atoi(tc);
}

void CmdInit()
{
	int sy = scr_h - msgh - comh;
	for (int ny = sy; ny < scr_h - msgh; ny++)
	{
		move(ny, 0);
		clrtoeol();
	}
	move(sy, 0);
}

int InputNum(int max)
{
	while (1)
	{
		int n;
		move(scr_h - msgh - 1, 0);
		clrtoeol();
		printw(">");
		echo();
		scanw("%d", &n);
		noecho();
		if (n > 0 && n <= max)
		{
			return n;
		}
		else if (n == 0)
		{
			return 0;
		}
		ExceptionProc();
	}
}

int AtkCnt(int told, int def, int cc)
{
	if (!told)
	{
		return 0;
	}
	int cm = -1;
	if (Prob(cc))
	{
		cm = -2;
	}
	int tmp = told * (0.8 + 0.1 * (rand() % 4)) - def;
	// msg.print("told %d def %d cc %d tmp %d", told, def, cc, tmp);
	if (tmp > 1)
	{
		return cm * tmp;
	}
	else
	{
		return cm;
	}
}

int SplashDmg(pos cp, pos np, int rng, int dmg)
{
	double inf = 1 - sqrt(cp + np) / rng;
	if (inf <= 0)
	{
		return 0;
	}
	double td = (inf * inf + inf) * dmg + 1;
	// msg.print("splash %lf %lf",inf,td);
	return td > 1 ? td : 0;
}

void Explode(pos cp, int eid)
{
	int rng = GetExRng(eid);
	int dmg = GetExDmg(eid);
	msg.print("A %s exploded", GetItemNm(eid));
	for (int i = 0; i < mobn; i++)
	{
		if (mob[i].id)
		{
			int atk = SplashDmg(cp, mob[i].p, rng, dmg);
			// msg.print("%d", atk);
			if (atk)
			{
				if (mob[i].Adjhlth(AtkCnt(atk, mob[i].GetDef(), 0), 3, eid))
				{
					mob[i].Reset();
				}
				if (mob[i].p + player.p <= mob[i].GetSrng() + player.GetAtt()
					&& !IsColls(mob[i].p, player.p))
				{
					mob[i].AIFb(1, -1);
				}
			}
		}
	}
	if (player.health)
	{
		int atk = SplashDmg(cp, player.p, rng, dmg);
		// msg.print("%d", atk);
		player.Adjhlth(AtkCnt(atk, player.GetDef(), 0), 3, eid);
	}
}

int randr(int min, int max)
{
	return min + rand() % (max - min + 1);
}

int Prob(int pct)
{
	return rand() % 100 < pct ? 1 : 0;
}

void ExceptionProc()
{
	msg.print("Input error, please try again.");
	msg.Show();
}

void MkGdir()
{
	crtdir(GDIR);
	crtdir(PDIR);
	crtdir(WDIR);
}

void crtdir(const char *dir)
{
	mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
}

int SavW()
{
	FILE *wsav;
	char wdir[100] = WDIR "/Zion";
	const char *bnm = "/data";
	crtdir(wdir);
	strcat(wdir, bnm);
	if ((wsav = fopen(wdir, "wb")) == NULL)
	{
		msg.print("Failed to open.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("Saving %s...", world.name);
	msg.Show();
	refresh();
	fwrite(&world, sizeof(world), 1, wsav);
	fwrite(&tm, sizeof(tm), 1, wsav);
	for (int i = 0; i < mobn; i++)
	{
		fwrite(&mob[i], sizeof(mob[i]), 1, wsav);
	}
	for (int i = 0; i < wlth * wlth; i++)
	{
		fprintf(wsav, "%hu ", blk[i]);
	}
	if (fclose(wsav))
	{
		msg.print("Failed to close.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("%s saved successfully.", world.name);
	msg.Show();
	refresh();
	return 1;
}

int SavP()
{
	FILE *psav;
	char pdir[100] = PDIR "/Alpha";
	const char *pnm = "/data";
	crtdir(pdir);
	strcat(pdir, pnm);
	if ((psav = fopen(pdir, "wb")) == NULL)
	{
		msg.print("Failed to open.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("Saving %s...", player.name);
	msg.Show();
	refresh();
	fwrite(&player, sizeof(player), 1, psav);
	if (fclose(psav))
	{
		msg.print("Failed to close.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("%s saved successfully.", player.name);
	msg.Show();
	refresh();
	return 1;
}

int LoadW()
{
	FILE *wld;
	if ((wld = fopen(WDIR "/Zion/data", "rb")) == NULL)
	{
		msg.print("Failed to open.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("Loading world");
	msg.Show();
	refresh();
	fread(&world, sizeof(world), 1, wld);
	fread(&tm, sizeof(tm), 1, wld);
	for (int i = 0; i < mobn; i++)
	{
		fread(&mob[i], sizeof(mob[i]), 1, wld);
	}
	srand(world.seed);
	for (int i = 0; i < wlth * wlth; i++)
	{
		fscanf(wld, "%hu ", &blk[i]);
	}
	if (fclose(wld))
	{
		msg.print("Failed to close.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("%s loaded successfully.", world.name);
	msg.Show();
	refresh();
	return 1;
}

int LoadP()
{
	FILE *pld;
	if ((pld = fopen(PDIR "/Alpha/data", "rb")) == NULL)
	{
		msg.print("Failed to open.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("Loading player");
	msg.Show();
	refresh();
	fread(&player, sizeof(player), 1, pld);
	if (fclose(pld))
	{
		msg.print("Failed to close.");
		msg.Show();
		refresh();
		return 0;
	}
	msg.print("%s loaded successfully.", player.name);
	msg.Show();
	refresh();
	return 1;
}

int sign(long int n)
{
	if (n > 0)
	{
		return 1;
	}
	else if (n < 0)
	{
		return -1;
	}
	return 0;
}

int min(int n1, int n2)
{
	return n1 < n2 ? n1 : n2;
}

int max(int n1, int n2)
{
	return n1 > n2 ? n1 : n2;
}