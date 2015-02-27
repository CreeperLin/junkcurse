#include"thing.h"
using namespace std;
int thing::type()
{
	return GetItemType(GetCPid());
}

int thing::size()
{
	switch (GetCPid())
	{
	case 21:
		return 2;
	default:
		return 1;
	}
}

int thing::IsArm()
{
	switch (type())
	{
	case 8:
	case 9:
	case 10:
		return 1;
	}
	return 0;
}

int thing::GetCPid()
{
	if (id == -1)
	{
		for (int i = 0; i < pnum; i++)
		{
			int t = pid[i];
			switch (t)
			{
			case 21:
				return t;
			}
		}
	}
	return id;
}

int thing::IsAdable(int pid)
{
	switch (GetCPid())
	{
	case 21:
		switch (pid)
		{
		case 31:
			return 1;
		}
	}
	return 0;
}

void thing::Set(int nid, int namt, int nlvl,int nmod)
{
	id = nid;
	amt = namt;
	lvl = nlvl;
	mod = nmod;
}
