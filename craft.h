#ifndef _CRAFT_H_
#define _CRAFT_H_
int IsCraftable(int id);
void CrGetIng(int oid);
int prtcr();
void CrReset();
void SetCrIng(int id, int amt);
int GetCrMaxa();
void CraftItem(int obid,int amt);
#endif
