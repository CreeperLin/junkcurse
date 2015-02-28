#ifndef _TIMER_H_
#define _TIMER_H_
class timer
{
public:
int id;
int intv;
int ct;
void Set(int nid,int nintv);
void Reset();
int Tick();
};
#endif
