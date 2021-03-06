#include "main.h"
using namespace std;
CStatdb Statdb;
CWorld world;
unsigned short int blk[wlth * wlth];
gtime tm;
CPlayer player;
CMob mob[mobn];
MsgBox msg;
int main()
{
	initscr();
	noecho();
	start_color();
	initattr();
	getmaxyx(stdscr, scr_h, scr_w);
	MkGdir();
	msg.Reset();
	while (1)
	{
		GReset();
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
		prthud();
		while (1)
		{
			int key = KeyEvent();
			if (key == 0)
			{
				int cmd = Command();
				if (cmd == 1)
				{
					break;
				}
				else if (cmd == -1)
				{
					continue;
				}
			}
			else if (key == -1)
			{
				continue;
			}
			prthud();
			if (player.health <= 0)
			{
				sleep(2);
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