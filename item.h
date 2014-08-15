#ifndef _ITEM_H_
#define _ITEM_H_
#include "thing.h"
#include "pos.h"
class item:public thing
{
public:
	unsigned int plc;
	pos p;
	void Reset();
	void Set(int nid, int namt, int nlvl, int nmod, int nplc, pos np);
};
int IsItemArnd(int nid);
int IsItemNear(pos p, int isp);
int IsItemNear(pos p, int isp, int nid);
void AddItem(int nid, int namt, int nlvl, int nmod, int nplc, pos np);
#endif