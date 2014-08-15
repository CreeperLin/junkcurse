#ifndef _RES_H_
#define _RES_H_
#include "cre.h"
const char* GetBuffNm(int id);
int GetEraStart(int era);
const char* GetMobNm(int id);
int GetMobInitSte(int id);
int GetMobEraS(int id);
int GetMobEraE(int id);
int GetMobRarity(int id);
int GetMobBuff(int id);
int GetMobBuffP(int id);
int GetMobBuffD(int id);
int GetMobMhlth(int id);
int GetMobMatk(int id);
int GetMobRatk(int id);
int GetMobDef(int id);
int GetMobRng(int id);
int GetMobSrng(int id);
int GetMobSpd(int id);
int GetMobAtt(int id);
int GetMobSize(int id);
int GetDm(int id);
int GetDmt(int id);
int GetDe(int id);
int GetItemMxstk(int id);
const char *GetBlkNm(int id);
const char *GetItemNm(int id);
int GetItemValue(int id);
int GetItemBuff(int id);
int GetItemBuffP(int id);
int GetItemBuffD(int id);
int GetItemType(int id);
int GetItemMpc(int id);
int GetItemAtt(int id);
int GetItemDmg(int id);
int GetItemDef(int id);
int GetItemRng(int id);
int GetItemCc(int id);
int GetItemFd(int id);
int GetItemFm(int id);
int GetAmmoType(int wid);
int GetItemAdmg(int id);
int GetExRng(int id);
int GetExDmg(int id);
#endif