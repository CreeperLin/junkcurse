#include "timer.h"
using namespace std;
int timer::Tick()
{
	if (intv == -1)
	{
		return 0;
	}
	ct--;
	if (ct <= 0)
	{
		Reset();
		return 1;
	}
	return 0;
}

void timer::Set(int nid, int nintv)
{
	id = nid;
	intv = nintv;
	ct = nintv;
}

void timer::Reset()
{
	id = 0;
	intv = 0;
	ct = 0;
}