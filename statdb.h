#ifndef _STATDB_H_
#define _STATDB_H_
#include "def.h"
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
	// todo effect
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
	// TODO craft recipe
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
	char *quote[3];
	// TODO effect
	// ToDo drops
	//TODO relation
};

class CMobNPCStatdb:public CMobStatdb
{
  public:
	// TODO sells
};

class CStatdb
{
  public:
	CStatdb();
	CMobStatdb MobStat[mobid];
	CItemStatdb ItemStat[itemid];
	CBlkStatdb BlkStat[blkid];
	CBufStatdb BufStat[bufid];
	CEventStatdb EventStat;
};
#endif