#include "main.h"
using namespace std;
unsigned int gtime::GetSe()
{
	return ((d / 90) % 4) + 1;
}

unsigned int gtime::IsNt()
{
	return (h >= 6 && h < 18) ? 0 : 1;
}

void gtime::DChg(int nd)
{
	if (nd)
	{
		world.Update();
		world.nmist += nd;
		world.nwthr += nd;
	}
}

void gtime::Exchg()
{
	int cse = GetSe(), nt = IsNt();
	int th = m / 60;
	h += th;
	m -= th * 60;
	int td = h / 24;
	d += td;
	h -= td * 24;
	DChg(td);
	if (nt)
	{
		if (h >= 6 && h < 18)
		{
			msg.print("The morning sun has vanquished the horrible night.");
			msg.SetAttr(12);
		}
	}
	else
	{
		if (h < 6 || h >= 18)
		{
			msg.print("What a horrible night to have a curse.");
			msg.SetAttr(12);
			nt = 1;
		}
	}
	int se = GetSe();
	if (cse != se)
	{
		switch (cse)
		{
		case 1:
			msg.print("The Spring has come.");
			break;
		case 2:
			msg.print("The Summer has come.");
			break;
		case 3:
			msg.print("The Autumn has come.");
			break;
		case 4:
			msg.print("The Winter has come.");
			break;
		}
		msg.SetAttr(12);
	}
}

void gtime::Reset()
{
	m = 0;
	h = 6;
	d = 1;
}

void gtime::Set(int nm, int nh, int nd)
{
	m = nm;
	h = nh;
	d = nd;
	Exchg();
}

void gtime::Adj(int nm, int nh, int nd)
{
	m += nm;
	h += nh;
	d += nd;
	DChg(nd);
	Exchg();
}