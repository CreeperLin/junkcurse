#ifndef _MOB_H_
#define _MOB_H_
#include "cre.h"
class CMob:public cre
{
  public:
	int sbj;
	int tgt;
	int ste;
	int lst;
	const char *name();
	void Atk(int obj,int dt);
	int SlctTgt();
	void Mmove(int dir);
	void Mmove(pos op);
	int FindMob(int nid);
	void AIAct();
	void AIFb(int msg, int tag);
	int GetMhlth();
	int GetMatk();
	int GetRatk();
	int GetDef();
	int GetRng();
	int GetSrng();
	int GetSpd();
	int GetMcc();
	int GetRcc();
	int GetAtt();
	int GetSize();
	void Spawn(int tid,int num,pos sp);
	int Speak(int sit);
	void Reset();
	void Drop();
};
void MobSpawn();
void SpawnMob(int id,pos p);
int SlctMob();
int SpawnChk(int id, int tid);
void SetSpnEnv();
#endif