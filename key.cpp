#include "main.h"
using namespace std;
unsigned key[25];
int KeyEvent()
{
	unsigned int ch = getch();
	if (ch == key[0])
	{
		return 0;
	}
	else if (ch == key[1])
	{
		player.Move(1);
	}
	else if (ch == key[2])
	{
		player.Move(5);
	}
	else if (ch == key[3])
	{
		player.Move(7);
	}
	else if (ch == key[4])
	{
		player.Move(3);
	}
	else if (ch == key[5])
	{
		player.Move(8);
	}
	else if (ch == key[6])
	{
		player.Move(2);
	}
	else if (ch == key[7])
	{
		player.Move(6);
	}
	else if (ch == key[8])
	{
		player.Move(4);
	}
	else if (ch == key[9])
	{
		player.Inv();
		clear();
	}
	else if (ch == key[10])
	{
		if (player.isrun)
		{
			msg.print("You slowed down.");
		}
		else
		{
			msg.print("You started to run.");
		}
		player.isrun = !player.isrun;
	}
	else if (ch == key[11])
	{
		player.Sleep();
	}
	else if (ch == key[12])
	{
		player.Kill();
	}
	else if (ch == key[13])
	{
		prtcr();
	}
	else if (ch == key[14])
	{
		player.Talk();
	}
	else if (ch == key[15])
	{
		msg.print("You rested for a while.");
		player.Adjhlth(5,0,0);
		player.Adjmana(5,0,0);
		tm.Adj(4, 0, 0);
		Refresh();
	}
	else if (ch == key[16])
	{
		world.Pick();
	}
	else if (ch == key[17])
	{
		world.Chop();
	}
	else if (ch == key[18])
	{
		world.Dig();
	}
	else if (ch == key[19])
	{
		player.Remove();
	}
	else if (ch == key[20])
	{
		Obsrv();
	}
	else if (ch == key[21])
	{
		player.Collect();
	}
	else if (ch == key[22])
	{
		player.Qhlth();
	}
	else if (ch == key[23])
	{
		player.Qmana();
	}
	else
	{
		return -1;
	}
	return 1;
}

void KeyReset()
{
	key[0] = ' ';
	key[1] = 'w';
	key[2] = 's';
	key[3] = 'a';
	key[4] = 'd';
	key[5] = 0;
	key[6] = 0;
	key[7] = 0;
	key[8] = 0;
	key[9] = 'e';
	key[10] = 'q';
	key[11] = 'z';
	key[12] = 'k';
	key[13] = 'c';
	key[14] = 't';
	key[15] = 'r';
	key[16] = 'p';
	key[17] = 'o';
	key[18] = 'i';
	key[19] = 'm';
	key[20] = 'l';
	key[21] = 'n';
	key[22] = 'h';
	key[23] = 'b';
	key[24] = 'g';
}

const char *GetKeyNm(int id)
{
	switch (id)
	{
	case 0:
		return "command";
	case 1:
		return "north";
	case 2:
		return "south";
	case 3:
		return "west";
	case 4:
		return "east";
	case 5:
		return "northwest";
	case 6:
		return "northeast";
	case 7:
		return "southwest";
	case 8:
		return "southeast";
	case 9:
		return "inventory";
	case 10:
		return "run";
	case 11:
		return "sleep";
	case 12:
		return "kill";
	case 13:
		return "craft";
	case 14:
		return "talk";
	case 15:
		return "rest";
	case 16:
		return "pick";
	case 17:
		return "chop";
	case 18:
		return "dig";
	case 19:
		return "remove";
	case 20:
		return "look";
	case 21:
		return "collect";
	case 22:
		return "quick health";
	case 23:
		return "quick mana";
	case 24:
		return "quick buff";
	}
}

void KeySet()
{
	clear();
	while (1)
	{
		for (int i = 0; i < 25; i++)
		{
			printw("%2d. %-20s ", i + 1, GetKeyNm(i));
			switch (key[i])
			{
			case 0:
				printw("none");
				break;
			case ' ':
				printw("space");
				break;
			case '\n':
				printw("enter");
				break;
			default:
				printw("%c", key[i]);
			}
			printw("\n");
		}
		printw("select key, 0 to exit\n");
		int tk = InputNum(25);
		if (!tk)
		{
			return;
		}
		printw("press a key\n");
		int ch = getch();
		key[--tk] = ch;
		for (int i = 0; i < 25; i++)
		{
			if (i != tk && key[i] && key[tk] && key[i] == key[tk])
			{
				key[i] = 0;
				printw("%s key reset!\n", GetKeyNm(i));
			}
		}
	}
}