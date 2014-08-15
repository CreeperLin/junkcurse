#include "main.h"
using namespace std;
int BlcSlctm(int oid, int sid)
{
	if (!sid)
	{
		switch (oid)
		{
		case 13:
			return 1;
		case 15:
			if (tm.IsNt())
			{
				return 1;
			}
		}
		return 0;
	}
	switch (oid)
	{
	case 3:
		switch (sid)
		{
		case 3:
		case 13:
		case 7:
			return 0;
		default:
			return 1;
		}
	case 4:
		return 0;
	case 6:
		switch (sid)
		{
		case 13:
		case 7:
			return 0;
		default:
			return 1;
		}
	case 11:
		return (sid != 14);
	case 13:
		return 1;
	case 14:
		return sid != 18;
	case 16:
		return sid != 20;
	default:
		switch (sid)
		{
		case 3:
			return 1;
		default:
			return 0;
		}
	}
	return 0;
}

int BlcSlctp(int oid)
{
	switch (oid)
	{
	case 3:
#if devmode
		return !player.IsEquipped(33);
#else
		return 1;
#endif
	case 6:
	case 13:
		return 1;
	}
	return 0;
}

int BlcSlcta(int oid)
{
	switch (oid)
	{
	case 6:
	case 9:
	case 11:
	case 12:
	case 13:
	case 14:
	case 16:
		return 1;
	}
	return 0;
}

int BlcSlctb(int cid, int fid)
{
	if (cid == fid)
	{
		return 0;
	}
	return BlcSlcta(fid);
}

int BlcSlcts(int cid, int fid)
{
	if (cid == fid)
	{
		return 0;
	}
	return BlcSlcta(fid) + BlcSlcta(cid);
}

int IsColls(pos sp, pos dp)
{
	int n, x1, y1, cid = blk[sp.geti()];
	pos tp1, tp2;
	while (sp != dp)
	{
		x1 = sign(dp.x - sp.x);
		y1 = sign(dp.y - sp.y);
		n = GetDir(sp, dp);
		sp.x += x1;
		sp.y += y1;
		tp2 = sp;
		tp1 = tp2;
		int b1 = blk[sp.geti()];
		if (BlcSlcts(b1, cid))
		{
			return 1;
		}
		if (n == 2 || n == 4 || n == 6 || n == 8)
		{
			tp1.x -= x1;
			tp2.y -= y1;
			int b2 = blk[tp1.geti()], b3 = blk[tp2.geti()];
			if (BlcSlcts(b2, cid) && BlcSlcts(b3, cid))
			{
				return 1;
			}
		}
	}
	return 0;
}

int IsCollb(pos sp, pos dp)
{
	int n, x1, y1, cid = blk[sp.geti()];
	pos tp1, tp2;
	while (sp != dp)
	{
		x1 = sign(dp.x - sp.x);
		y1 = sign(dp.y - sp.y);
		n = GetDir(sp, dp);
		sp.x += x1;
		sp.y += y1;
		tp2 = sp;
		tp1 = tp2;
		int b1 = blk[sp.geti()];
		if (BlcSlctb(b1, cid))
		{
			return 1;
		}
		if (n == 2 || n == 4 || n == 6 || n == 8)
		{
			tp1.x -= x1;
			tp2.y -= y1;
			int b2 = blk[tp1.geti()], b3 = blk[tp2.geti()];
			if (BlcSlctb(b2, cid) && BlcSlctb(b3, cid))
			{
				return 1;
			}
		}
	}
	return 0;
}

int IsCollm(int id, pos tp, int n)
{
	pos tp1, tp2;
	int x1 = dtox(n);
	int y1 = dtoy(n);
	tp.x += x1;
	tp.y += y1;
	tp2 = tp;
	tp1 = tp2;
	if (BlcSlctm(blk[tp.geti()], id))
	{
		return 1;
	}
	if (n == 2 || n == 4 || n == 6 || n == 8)
	{
		tp1.x = tp.x - x1;
		tp2.y = tp.y - y1;
		if (BlcSlctm(blk[tp1.geti()], id) && BlcSlctm(blk[tp2.geti()], id))
		{
			return 1;
		}
	}
	return 0;
}

int IsCollp(int n)
{
	pos tp = player.p, tp1, tp2;
	int x1 = dtox(n);
	int y1 = dtoy(n);
	tp.x += x1;
	tp.y += y1;
	tp2 = tp;
	tp1 = tp2;
	if (BlcSlctp(blk[tp.geti()]))
	{
		return 1;
	}
	if (n == 2 || n == 4 || n == 6 || n == 8)
	{
		tp1.x = tp.x - x1;
		tp2.y = tp.y - y1;
		if (BlcSlctp(blk[tp1.geti()]) && BlcSlctp(blk[tp2.geti()]))
		{
			return 1;
		}
	}
	return 0;
}