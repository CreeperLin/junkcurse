#ifndef _STATDB_H_
#define _STATDB_H_
#include "def.h"
struct StatEffect
{
	int type;
	int val1;
	int val2;
};

struct StatRecipe
{
	int type;
	int amt;
};

struct StatDrop
{
	int type;
	int amin;
	int amax;
	int rate;
};

class CEventStatdb
{
  public:
	const char *name;
	// TODO effect&type
};

class CBufStatdb
{
  public:
	const char *name;
	StatEffect bufx;
};

class CBlkStatdb
{
  public:
	const char *name;
	int colltyp;
};

class CItemStatdb
{
  public:
	const char *name;
	int mxstk;
	int val;
	int type;
	int att;
	StatRecipe crftrcp[maxi];
};

class CItemConsumStatdb:public CItemStatdb
{
  public:
	int fedtyp;
	int fedval;
};

class CItemWpnStatdb:public CItemStatdb
{
  public:
	int wpntyp;
	int wpndmg;
	int wpncric;
	StatEffect wpnfx;
};

class CItemWpnMnStatdb:public CItemWpnStatdb
{
  public:
	int mpcost;
};
class CItemWpnRgStatdb:public CItemWpnStatdb
{
  public:
	int amotyp;
};

class CItemWearStatdb:public CItemStatdb
{
  public:
	int amrdef;
};

class CItemAccStatdb:public CItemStatdb
{
  public:
	StatEffect accfx[5];
};

class CItemAmmoStatdb:public CItemStatdb
{
  public:
	int amodmg;
};

class CMobStatdb
{
  public:
	const char *name;
	int ht;
	int mt;
	int mlatk;
	int rgatk;
	int mnatk;
	int def;
	int rng;
	int srng;
	int spd;
	int att;
	int size;
	int ste;
	int dexp;
	int colltyp;
	int rarity;
	const char *quote[20];
	StatEffect mlbuf;
	StatEffect rgbuf;
	StatEffect mnbuf;
	StatDrop drop[10];
	//TODO relation
	//todo spawn condition
};

class CMobNPCStatdb:public CMobStatdb
{
  public:
	int sellcur;
	int sellid[maxs];
};

class CStatdb
{
  public:
	void Reset();
	void DumpRes();
	void AddMob();
	void AddItem();
	void AddBlk();
	void AddBuf();
	void AddEvt();
	void ChgMob();
	void ChgItem();
	void ChgBlk();
	void ChgBuf();
	void ChgEvt();
	int mobc;
	int itmc;
	int blkc;
	int bufc;
	int evtc;
	CMobStatdb* MobStat[mobid];
	CItemStatdb* ItemStat[itmid];
	CBlkStatdb* BlkStat[blkid];
	CBufStatdb* BufStat[bufid];
	CEventStatdb* EventStat[evtid];
};
#endif