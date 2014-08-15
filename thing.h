#ifndef _THING_H_
#define _THING_H_
#include "def.h"
#include "res.h"
class thing
{
  public:
	unsigned int id;
	unsigned pid[pnum];
	int pamt[pnum];
	int amt;
	int lvl;
	unsigned int mod;
	int type();
	int size();
	int IsArm();
	int GetCPid();
	int IsAdable(int pid);
	void Set(int nid,int namt,int nlvl,int nmod);
};
#endif