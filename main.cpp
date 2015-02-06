#include "maind.h"
using namespace std;
int main()
{
	initscr();
	noecho();
	start_color();
	initattr();
	getmaxyx(stdscr,scr_h,scr_w);
	MkGdir();
	while (1)
	{
		{
			int start = GameStart();
			if (!start)
			{
				break;
			}
			if (start == -1)
			{
				continue;
			}
		}
		msg.Init(ctop(0,scr_h-msgh),ctop(scr_w-1,scr_h-1));
		msg.ena=0;
		while (1)
		{
			if (!KeyEvent())
			{
				if (Command())
				{
					break;
				}
			}
			if (player.health <= 0)
			{
				prthud();
				delay(2);
				prtpldth();
				int trspn = InputNum(1);
				player.Respawn();
				if (trspn == 0)
				{
					SavW();
					SavP();
					break;
				}
				clear();
				prthud();
				msg.print("You woke up in the %s.",
					   GetBlkNm(blk[player.p.geti()]));
				SetSpnEnv();
			}
			prthud();
		}
	}
	endwin();
	return 0;
}

void Refresh()
{
	player.Update();
	world.EventUpdate();
	world.EventProducer();
	for (int i = 0; i < mobn; i++)
	{
		if (mob[i].id)
		{
			if (player.p + mob[i].p > 100)
			{
				//msg.print("A %s has been wiped out", mob[i].name());
				mob[i].Reset();
			}
		}
	}
	MobSpawn();
	for (int i = 0; i < mobn; i++)
	{
		if (mob[i].id)
		{
			if (mob[i].Update())
			{
				mob[i].Reset();
				continue;
			}
			mob[i].AIAct();
		}
	}
}