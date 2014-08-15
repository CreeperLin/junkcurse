#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "pos.h"
void GenVillages(int num);
void GenVillage(pos cp);
void GenerateW();
void ClrBlk(int id,int rid);
int IsBlkArnd(pos cp,int rng,int id);
int IsBlkPlc(int id);
int GetBiome(pos cp);
void SetReg(pos p, unsigned int l, unsigned int w, int nid);
int IsRegClear(pos p, unsigned int l, unsigned int w, int nid);
unsigned long int blki(int x, int y);
#endif