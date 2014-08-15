#ifndef _GTIME_H_
#define _GTIME_H_
class gtime
{
public:
	int m;
	int h;
	int d;
	unsigned int GetSe();
	unsigned int IsNt();
	void DChg(int nd);
	void Exchg();
	void Reset();
	void Set(int nm,int nh,int nd);
	void Adj(int nm,int nh,int nd);
};
#endif

