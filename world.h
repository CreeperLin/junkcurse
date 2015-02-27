#ifndef _WORLD_H_
#define _WORLD_H_
#include "pos.h"
#include "timer.h"
#include "def.h"
#include "item.h"
class CWorld
{
  public:
	unsigned version;
	unsigned long int seed;
	int era;
	pos wspn;
	char name[10];
	int ppbr, pcwd, ppa, pdc, cwdt, dct;
	int nwthr, nrain, nievt, nmist;
	timer wtimer[evtn];
	item witem[inum];
	void Reset();
	void Init();
	void Update();
	void EraUpdate();
	void AdjGaP(int &p, int n);
	int GetCpwdP();
	int GetPbrP();
	int GetPaP();
	int GetDcP();
	int Chop();
	int Pick();
	int Dig();
	void InitEvent();
	int EventUpdate();
	void WipeEvent(int nid);
	void WipeEventa();
	int IsEvent(int nid);
	void AddEvent(int nid, int nintv);
	void EventProducer();
};
#endif
