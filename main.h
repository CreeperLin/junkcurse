#ifndef _MAIN_H_
#define _MAIN_H_
#include "world.h"
#include "block.h"
#include "basic.h"
#include "craft.h"
#include "trade.h"
#include "output.h"
#include "colldt.h"
#include "res.h"
#include "def.h"
#include "pos.h"
#include "cre.h"
#include "mob.h"
#include "player.h"
#include "thing.h"
#include "item.h"
#include "inv.h"
#include "gtime.h"
#include "timer.h"
#include "key.h"
#include "msgbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <ncurses.h>
void Refresh();
extern CWorld world;
extern unsigned short int blk[wlth * wlth];
extern gtime tm;
extern CPlayer player;
extern CMob mob[mobn];
extern item witem[inum];
extern MsgBox msg;
extern int fbio,maxspn, spnrt, tolspn;
#endif