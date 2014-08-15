#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cre.h"
#include "inv.h"
class CPlayer:public cre
{
  public:
	char name[10];
	long int exp;
	int isrun;
	int mp;
	int mxmp;
	int ptgt;
	pos spn;
	inv slot[30];
	void Collect();
	void Remove();
	void Kill();
	void Talk();
	void Inv();
	void Qhlth();
	void Qmana();
	int IsGrab(int nid);
	int IsEquipped(int nid);
	int GetAtk(int n);
	int GetMpc(int wid);
	int GetDef();
	int GetRng();
	int GetSrng();
	int GetSpd();
	int GetCc(int n);
	int GetAtt();
	int Adjmana(int n,int evt,int obj);
	void AddExp(int aexp);
	void Reset();
	void Respawn();
	void Sleep();
	void Unequip(int n);
	void AddInv(int stn,int nid, int namt, int nlvl, int nmod);
	void AddInv(int nid, int namt, int nlvl, int nmod);
	void DecInv(int nid, int namt);
	void SwapInv(int n1, int n2);
	int GetInvAmt(int nid);
	void Move(int n);
};
void SetPlpos();
#endif