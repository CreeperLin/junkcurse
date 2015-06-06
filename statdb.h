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
	int rate;
};

class CEventStatdb
{
  public:
	char *name;
	// TODO effect&type
};

class CBufStatdb
{
  public:
	char *name;
	StatEffect bufx;
};

class CBlkStatdb
{
  public:
	char *name;
	int colltyp;
};

class CItemStatdb
{
  public:
	char *name;
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
	//TODO weapon effect
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
	char *name;
	int ht;
	int mt;
	int matk;
	int ratk;
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
	char *quote[15];
	StatEffect bufcst[5];
	StatDrop drop[10];
	//TODO relation
};

class CMobNPCStatdb:public CMobStatdb
{
  public:
	int sellid[maxs];
};

class CStatdb
{
  public:
	CStatdb();
	CMobStatdb MobStat[mobid];
	CItemStatdb ItemStat[itmid];
	CBlkStatdb BlkStat[blkid];
	CBufStatdb BufStat[bufid];
	CEventStatdb EventStat;
};
#endif