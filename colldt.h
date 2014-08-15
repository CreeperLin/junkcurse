#ifndef _COLLDT_H_
#define _COLLDT_H_
#include "pos.h"
int BlcSlctm(int oid, int sid);
int BlcSlctp(int oid);
int BlcSlcta(int oid);
int BlcSlctb(int cid, int fid);
int BlcSlcts(int cid, int fid);
int IsColls(pos sp, pos dp);
int IsCollb(pos sp, pos dp);
int IsCollm(int id,pos tp, int n);
int IsCollp(int n);
#endif