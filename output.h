#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include <ncurses.h>
extern int scr_w, scr_h;
extern attr_t attr[17];
int cx();
int cy();
void printwr(const char *ch, ...);
void printwr(int attn, const char *ch, ...);
void initattr();
void prtbuff(int bid, int sbj, int obj);
void prtadjm(int n, int sbj, int evt, int obj);
void prtadjh(int n,int sbj,int evt,int obj);
void prtdmsg(int sbj,int evt,int obj);
void prtbar(int val,int max);
void prtmain();
void prtpldth();
void prthud();
void Obsrv();
int prtmb(int rng);
void prthmp(int wid);
void prtfmp(int rng);
void prtmp(int rng);
void prtime();
void prtsinv(int n);
void prtinv();
void prtcrash();
void prtwst();
void prtst();
void prtmst(int n);
#endif
