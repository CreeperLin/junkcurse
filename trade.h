#ifndef _TRADE_H_
#define _TRADE_H_
int GetCurr(int mid);
const char* GetCurrNm(int id);
void SetSell(int mid);
void AddSell(int nid);
void TrReset();
void prtsell(int mid);
void prtrd(int mid);
#endif
