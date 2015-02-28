#ifndef _INV_H_
#define _INV_H_
#include "thing.h"
class inv:public thing
{
public:
void Reset();
void Adj(int namt);
int Decraft(int n);
int Decrafta();
int Adapt(int cnum);
};
#endif
