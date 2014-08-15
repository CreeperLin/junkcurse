#include "main.h"
using namespace std;
void GenVillages(int num)
{
	pos cp;
	int trys = 0, suc = 0, tol = 0;
	do
	{
		cp.Set(randr(700, 1400), randr(700, 1400));
		// msg.print("%d tol %d trys %d,%d.\n",tol,trys,cp.x,cp.y);
		if (!IsRegClear(ctop(cp.x - 6, cp.y - 6), 13, 13, 1)
			|| !(IsBlkArnd(cp, 10, 3) || IsBlkArnd(cp, 10, 4))
			|| cp + player.p < 100)
		{
			if (++trys > 100)
			{
				trys = 0;
				tol++;
				msg.print("skipped.\n");
			}
			if (tol > 100000)
			{
				break;
			}
			continue;
		}
		trys = 0;
		GenVillage(cp);
		tol++;
		msg.print("Village %d generated at %d,%d.\n", ++suc, cp.x, cp.y);
	}
	while (suc < num);
	msg.print("total trys %d suc %d\n", tol, suc);
}

void GenVillage(pos cp)
{
	int c = 0, t = 0, q = randr(8, 10), f = 0;
	do
	{
		pos hp = cp;
		int tl = randr(3, 4), tw = randr(3, 4);
		hp.x += (2 * randr(-1, 0) + 1) * randr(4, 15);
		hp.y += (2 * randr(-1, 0) + 1) * randr(4, 15);
		if (!IsRegClear(ctop(hp.x - 1, hp.y - 1), tl + 2, tw + 2, 1))
		{
			if (++t > 10000)
			{
				t = 0;
				c++;
				f++;
			}
			continue;
		}
		pos rop = hp;
		int exdir = 0;
		do
		{
			if (blk[rop.geti()] != 1 && blk[rop.geti()] != 15)
			{
				exdir = 2;
				break;
			}
			int cx = sign(cp.x - rop.x);
			int cy = sign(cp.y - rop.y);
			if (cx)
			{
				rop.x += cx;
			}
			else
			{
				rop.y += cy;
			}
		}
		while (rop != cp);
		rop = hp;
		do
		{
			if (blk[rop.geti()] != 1 && blk[rop.geti()] != 15)
			{
				exdir = !exdir ? 1 : -1;
				break;
			}
			int cx = sign(cp.x - rop.x);
			int cy = sign(cp.y - rop.y);
			if (cy)
			{
				rop.y += cy;
			}
			else
			{
				rop.x += cx;
			}
		}
		while (rop != cp);
		if (exdir == -1)
		{
			continue;
		}
		else if (!exdir)
		{
			exdir = randr(1, 2);
		}
		rop = hp;
		if (exdir == 1)
		{
			do
			{
				blk[rop.geti()] = 15;
				int cx = sign(cp.x - rop.x);
				int cy = sign(cp.y - rop.y);
				if (cx)
				{
					rop.x += cx;
				}
				else
				{
					rop.y += cy;
				}
			}
			while (rop != cp);
		}
		else
		{
			do
			{
				blk[rop.geti()] = 15;
				int cx = sign(cp.x - rop.x);
				int cy = sign(cp.y - rop.y);
				if (cy)
				{
					rop.y += cy;
				}
				else
				{
					rop.x += cx;
				}
			}
			while (rop != cp);
		}
		SetReg(hp, tl, tw, 16);
		c++;
	}
	while (c < q);
	if (c > f)
	{
		blk[cp.geti()] = 15;
	}
}

void GenerateW()
{
	clear();
	refresh();
	pos cp;
	for (int i = 0; i < wlth * wlth; i++)
	{
		blk[i] = 3;
	}
	cp.x = cp.y = (wlth - 1640) / 2;
	SetReg(cp, 1640, 1640, 7);
	pos dp = cp;
	dp.x += 20;
	dp.y += 20;
	SetReg(dp, 1600, 1600, 1);
	printwr(13,"Generating forest\n");
	for (int i = 0; i < randr(6000, 10000); i++)
	{
		pos fp = dp;
		int tl = randr(15, 20), tw = randr(15, 20);
		fp.x += randr(0, 1600 - tl);
		fp.y += randr(0, 1600 - tw);
		SetReg(fp, tl, tw, 2);
	}
	printwr("Generating jungle\n");
	for (int i = 0; i < randr(1500, 3200); i++)
	{
		pos jp = dp;
		int tl = randr(20, 30), tw = randr(20, 30);
		jp.x += randr(100, 1500 - tl);
		jp.y += randr(100, 1500 - tw);
		SetReg(jp, tl, tw, 8);
	}
	printwr("Generating swamp\n");
	for (int i = 0; i < randr(2000, 8000); i++)
	{
		pos sp = dp;
		int tl = randr(10, 20), tw = randr(10, 20);
		sp.x += randr(100, 1500 - tl);
		sp.y += randr(100, 1500 - tw);
		SetReg(sp, tl, tw, 10);
	}
	printwr("Generating mountain\n");
	for (int i = 0; i < randr(2000, 8000); i++)
	{
		pos mp = dp;
		int tl = randr(10, 20), tw = randr(10, 20);
		mp.x += randr(0, 1600 - tl);
		mp.y += randr(0, 1600 - tw);
		SetReg(mp, tl, tw, 5);
	}
	printwr("Generating pond\n");
	for (int i = 0; i < randr(5000, 14000); i++)
	{
		pos wp = dp;
		int tl = randr(3, 5), tw = randr(3, 5);
		wp.x += randr(100, 1500 - tl);
		wp.y += randr(100, 1500 - tw);
		SetReg(wp, tl, tw, 4);
	}
	printwr("Generating stream\n");
	for (int i = 0; i < randr(4000, 9000); i++)
	{
		pos pop = dp;
		int tl = randr(3, 5), tw = randr(3, 5);
		pop.x += randr(100, 1500 - tl);
		pop.y += randr(100, 1500 - tw);
		SetReg(pop, tl, tw, 3);
		if (Prob(40))
		{
			for (int j = 0; j < randr(0, 2); j++)
			{
				pos sp = pop;
				int dir = randr(1, 8);
				sp.x += (rand() % 2) * (tl - 1);
				sp.y += (rand() % 2) * (tw - 1);
				for (int k = 0; k < randr(20, 50); k++)
				{
					SetReg(sp, 1, 2, 3);
					if (Prob(20))
					{
						dir += randr(-2, 2);
						if (dir < 1)
						{
							dir += 8;
						}
						else if (dir > 8)
						{
							dir -= 8;
						}
					}
					sp.move(dir, 1);
				}
			}
		}
	}
	printwr("Generating desert\n");
	for (int i = 0; i < randr(30, 40); i++)
	{
		pos dep = dp;
		int tl = randr(60, 70), tw = randr(60, 70);
		dep.x += randr(0, 1600 - tl);
		dep.y += randr(0, 1600 - tw);
		SetReg(dep, tl, tw, 7);
	}
	printwr("Generating grassland\n");
	for (int i = 0; i < randr(90, 200); i++)
	{
		pos gp = dp;
		int tl = randr(40, 60), tw = randr(40, 60);
		gp.x += randr(100, 1500 - tl);
		gp.y += randr(100, 1500 - tw);
		SetReg(gp, tl, tw, 1);
	}
	printwr("Generating river.\n");
	for (int i = 0; i < randr(3, 5); i++)
	{
		pos rp = cp;
		int dir;
		switch (randr(1, 4))
		{
		case 1:
			rp.y += randr(200, 1400);
			dir = randr(2, 4);
			break;
		case 2:
			rp.x += 1640;
			rp.y += randr(200, 1400);
			dir = randr(6, 8);
			break;
		case 3:
			rp.x = randr(200, 1400);
			dir = randr(4, 6);
			break;
		case 4:
			rp.x = randr(200, 1400);
			rp.y = 1640;
			dir = rand() % 3 ? randr(1, 2) : 8;
			break;
		}
		for (int k = 0; k < randr(100, 200); k++)
		{
			for (int tx = rp.x - 1; tx <= rp.x + 1; tx += 2)
			{
				blk[blki(tx, rp.y)] = 3;
			}
			for (int ty = rp.y - 1; ty <= rp.y + 1; ty++)
			{
				blk[blki(rp.x, ty)] = 3;
			}
			if (Prob(10))
			{
				dir += randr(-2, 2);
				if (dir < 1)
				{
					dir += 8;
				}
				else if (dir > 8)
				{
					dir -= 8;
				}
			}
			rp.move(dir, 1);
		}
	}
	printwr("Generating lake\n");
	for (int i = 0; i < randr(3, 5); i++)
	{
		pos lp = dp;
		int tl = randr(30, 40), tw = randr(30, 40);
		lp.x += randr(100, 1500 - tl);
		lp.y += randr(100, 1500 - tw);
		SetReg(lp, tl, tw, 3);
	}
	printwr("Generating peak\n");
	for (int i = 0; i < randr(3, 4); i++)
	{
		pos pp, hp = dp;
		int tl = randr(50, 60), tw = randr(50, 60);
		hp.x += randr(0, 1600 - tl);
		hp.y += randr(0, 1600 - tw);
		SetReg(hp, tl, tw, 5);
		for (int j = 0; j < randr(1, 2); j++)
		{
			pp.x = hp.x + randr(5, tl / 3);
			pp.y = hp.y + randr(5, tw / 3);
			SetReg(pp, randr(5, tl / 3), randr(5, tw / 3), 6);
		}
	}
	printwr("Generating bush\n");
	for (int i = 0; i < randr(1400, 3000); i++)
	{
		int cx, cy;
		do
		{
			cx = randr(700, 1400);
			cy = randr(700, 1400);
		}
		while (blk[blki(cx, cy)] != 2);
		SetReg(ctop(cx, cy), randr(2, 3), randr(2, 3), 9);
	}
	printwr("Generating hut\n");
	for (int i = 0; i < 500; i++)
	{
		int cx, cy;
		do
		{
			cx = randr(700, 1400);
			cy = randr(700, 1400);
		}
		while (!IsRegClear(ctop(cx - 1, cy - 1), 4, 4, 2));
		SetReg(ctop(cx, cy), 2, 2, 11);
	}
	printwr("Generating cave\n");
	for (int i = 0; i < 200; i++)
	{
		int cx, cy;
		do
		{
			cx = randr(700, 1400);
			cy = randr(700, 1400);
		}
		while (!IsRegClear(ctop(cx - 1, cy - 1), 8, 8, 5));
		int tl = randr(5, 6), tw = randr(5, 6);
		SetReg(ctop(cx, cy), tl, tw, 13);
		switch (randr(1, 4))
		{
		case 1:
			cx++;
			tl -= 2;
			tw--;
			break;
		case 2:
			cx++;
			cy++;
			tl--;
			tw -= 2;
			break;
		case 3:
			cx++;
			cy++;
			tl -= 2;
			tw--;
			break;
		case 4:
			cy++;
			tl--;
			tw -= 2;
			break;
		}
		SetReg(ctop(cx, cy), tl, tw, 12);
	}
	printwr("Generating shed\n");
	for (int i = 0; i < 200; i++)
	{
		int cx, cy, trys = 0,skip=0;
		do
		{
			cx = randr(700, 1400);
			cy = randr(700, 1400);
			if (++trys > 1000)
			{
				trys = 0;
				//printwr("cancel.\n");
				skip=1;
				break;
			}
		}
		while (!IsRegClear(ctop(cx - 6, cy - 6), 13, 13, 1));
		int c=0;
		if (skip)
		{
			skip=0;
			continue;
		}
		do
		{
			pos shp = ctop(cx, cy);
			int tl = randr(3, 4), tw = randr(3, 4);
			shp.x += randr(-7, 7 - tl);
			shp.y += randr(-7, 7 - tw);
			if (!IsRegClear(ctop(shp.x - 1, shp.y - 1), tl + 2, tw + 2, 1))
			{
				if (++trys > 100)
				{
					trys = 0;
					c++;
					//printwr("skipped.\n");
				}
				continue;
			}
			SetReg(ctop(cx, cy), tl, tw, 14);
			c++;
		}
		while (c < 3);
	}
	printwr("Generating sea\n");
	for (int i = 0; i < randr(2, 3); i++)
	{
		pos sep;
		int tl = randr(400, 500), tw = randr(400, 500);
		switch (randr(1, 4))
		{
		case 1:
			sep.x = 100;
			sep.y = randr(100, 2040 - tw);
			break;
		case 2:
			sep.x = 2000 - tl;
			sep.y = randr(100, 2000 - tw);
			break;
		case 3:
			sep.x = randr(100, 2000 - tl);
			sep.y = 100;
			break;
		case 4:
			sep.x = randr(100, 2000 - tl);
			sep.y = 2000 - tw;
			break;
		}
		SetReg(sep, tl, tw, 7);
		sep.x += 5;
		sep.y += 5;
		tl -= 10;
		tw -= 10;
		SetReg(sep, tl, tw, 3);
		if (Prob(80))
		{
			printwr("Generating Island\n");
			for (int j = 0; j < randr(3, 5); j++)
			{
				pos ip = sep;
				ip.x += randr(tl / 10, tl - tl / 5);
				ip.y += randr(tl / 10, tl - tl / 5);
				tl = randr(40, 60);
				tw = randr(40, 60);
				SetReg(ip, tl, tw, 7);
				for (int k = 0; k < randr(2, 3); k++)
				{
					pos ifp;
					int tfw = randr(20, 30), tfl = randr(20, 30);
					ifp.x = ip.x + randr(5, tl - 5 - tfl);
					ifp.y = ip.y + randr(5, tw - 5 - tfw);
					SetReg(ifp, tfl, tfw, 2);
				}
			}
		}
	}

	SetReg(ctop(0, 0), 200, 1840, 3);
	SetReg(ctop(0, 1840), 1840, 200, 3);
	SetReg(ctop(1840, 200), 200, 1840, 3);
	SetReg(ctop(200, 0), 1840, 200, 3);
	printwr(11,"%s generated successfully\n", world.name);
}

void ClrBlk(int id, int rid)
{
	for (int i = 0; i < wlth * wlth; i++)
	{
		if (blk[i] == id)
		{
			blk[i] = rid;
		}
	}
}

int IsBlkArnd(pos cp, int rng, int id)
{
	for (int y = cp.y - rng; y <= cp.y + rng; y++)
	{
		int oy = cp.y - y;
		oy *= oy;
		int ox = sqrt(rng * rng - oy);
		for (int x = cp.x - ox; x <= cp.x + ox; x++)
		{
			if (blk[blki(x, y)] == id)
			{
				return 1;
			}
		}
	}
	return 0;
}

int IsBlkPlc(int id)
{
	switch (id)
	{
	case 3:
	case 4:
	case 9:
	case 13:
		return 0;
	default:
		return 1;
	}
}

int GetBiome(pos cp)
{
	int drng = 10, dsq = drng * drng, bioc[8];
	for (int i = 0; i < 8; i++)
	{
		bioc[i] = 0;
	}
	for (int cx = cp.x - drng; cx <= cp.x + drng; cx++)
	{
		for (int cy = cp.y - drng; cy <= cp.y + drng; cy++)
		{
			switch (blk[blki(cx, cy)])
			{
			case 1:
				bioc[1]++;
				break;
			case 2:
				bioc[2]++;
				break;
			case 3:
				bioc[3]++;
				break;
			case 5:
			case 6:
				bioc[4]++;
				break;
			case 7:
				bioc[5]++;
				break;
			case 8:
				bioc[6]++;
				break;
			case 10:
				bioc[7]++;
				break;
			default:
				bioc[0]++;
			}
		}
	}
	int maxb = 0;
	for (int i = 1; i < 8; i++)
	{
		if (bioc[maxb] < bioc[i])
		{
			maxb = i;
		}
	}
	if (bioc[maxb] > 0.4 * dsq)
	{
		return maxb;
	}
	return 0;
}

void SetReg(pos p, unsigned int l, unsigned int w, int nid)
{
	for (unsigned int i = p.y; i < p.y + w; i++)
	{
		for (unsigned int j = p.x; j < p.x + l; j++)
		{
			if (j < wlth && i < wlth)
			{
				blk[blki(j, i)] = nid;
			}
			else
			{
				msg.print("leak %d\n", nid);
			}
		}
	}
}

int IsRegClear(pos p, unsigned int l, unsigned int w, int nid)
{
	for (unsigned int cy = p.y; cy < p.y + w; cy++)
	{
		for (unsigned int cx = p.x; cx < p.x + l; cx++)
		{
			if (blk[blki(cx, cy)] != nid)
			{
				return 0;
			}
		}
	}
	return 1;
}

unsigned long int blki(int x, int y)
{
	unsigned long int tmp = y * wlth + x;
	if (tmp < wlth * wlth && tmp >= 0)
	{
		return tmp;
	}
	return 0;
}