#ifndef _BASIC_H_
#define _BASIC_H_
int GameStart();
int Command();
void GReset();
int GetPara();
void CmdInit();
int InputNum(int max);
int AtkCnt(int told, int def, int cc);
int SplashDmg(pos cp,pos np,int rng,int dmg);
void Explode(pos cp, int eid);
int randr(int min, int max);
int Prob(int pct);
void ExceptionProc();
void MkGdir();
void crtdir(const char* dir);
int SavW();
int SavP();
int LoadW();
int LoadP();
int sign(long int n);
int min(int n1,int n2);
int max(int n1,int n2);
void delay(double n);
#endif