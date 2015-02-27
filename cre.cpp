#include "main.h"
using namespace std;
int cre::Update()
{
	for (int i = 0; i < 10; i++)
	{
		if (buff[i].id)
		{
			buff[i].Tick();
			int hlth = 0;
			switch (buff[i].id)
			{
			case 1:
				hlth = -5;
				break;
			case 2:
				hlth = 5;
				break;
			case 3:
				hlth = -3;
				break;
			}
			if (Adjhlth(hlth,2,buff[i].id))
			{
				return 1;
			}
		}
	}
	return 0;
}

int cre::Adjhlth(int n, int evt, int obj)
{
	health += n;
	prtadjh(n, id, evt, obj);
	if (health <= 0)
	{
		health = 0;
		prtdmsg(id, evt, obj);
		return 1;
	}
	else if (health > maxhlth)
	{
		health = maxhlth;
	}
	return 0;
}

void cre::Wipebuff()
{
	for (int i = 0; i < 10; i++)
	{
		buff[i].Reset();
	}
}

void cre::Addbuff(int nid, int nintv,int obj)
{
	for (int i = 0; i < 10; i++)
	{
		if (!buff[i].id)
		{
			buff[i].Set(nid, nintv);
			prtbuff(nid,id,obj);
			return;
		}
		else if (buff[i].id == nid)
		{
			buff[i].intv = nintv;
			return;
		}
	}
}

int cre::Isbuff(int nid)
{
	for (int i = 0; i < 10; i++)
	{
		if (buff[i].id == nid)
		{
			return 1;
		}
	}
	return 0;
}

void cre::Wipebuff(int nid)
{
	for (int i = 0; i < 10; i++)
	{
		if (nid)
		{
			buff[i].Reset();
			return;
		}
	}
}
