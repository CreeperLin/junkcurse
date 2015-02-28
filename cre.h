#ifndef _CRE_H_
#define _CRE_H_
#include "pos.h"
#include "timer.h"
class cre
{
public:
	int id;
	int health;
	unsigned int maxhlth;
	unsigned int lvl;
	pos p;
	timer buff[10];
	int Update();
	int Adjhlth(int n,int evt,int obj);
	void Wipebuff();
	void Addbuff(int nid,int nintv,int obj);
	int Isbuff(int nid);
	void Wipebuff(int nid);
};
#endif
