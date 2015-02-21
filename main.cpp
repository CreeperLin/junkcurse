#include "maind.h"
using namespace std;
int main()
{
	initscr();
	noecho();
	start_color();
	initattr();
	getmaxyx(stdscr, scr_h, scr_w);
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
		msg.Show();
		refresh();
		while (1)
		{
			if (!KeyEvent())
			{
				if (Command())
				{
					break;
				}
			}
			prthud();
			if (player.health <= 0)
			{
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
				msg.print(13, "You woke up in the %s.", GetBlkNm(blk[player.p.geti()]));
				prthud();
				SetSpnEnv();
			}
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
				// msg.print("A %s has been wiped out", mob[i].name());
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