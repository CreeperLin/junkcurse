#include "main.h"
using namespace std;
int Iid[maxi], Iamt[maxi], cing = 0;
int IsCraftable(int id)
{
	switch (id)
	{
	case 4:
	case 5:
	case 6:
		if (IsItemArnd(25))
		{
			return 1;
		}
		break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 23:
	case 36:
	case 37:
	case 39:
		if (IsItemArnd(24))
		{
			return 1;
		}
		break;
	case 24:
	case 25:
	case 26:
		return 1;
	}
	return 0;
}

void CrGetIng(int oid)
{
	switch (oid)
	{
	case 4:
		SetCrIng(1, 1);
		SetCrIng(8, 1);
		break;
	case 5:
		SetCrIng(2, 1);
		SetCrIng(8, 1);
		break;
	case 6:
		SetCrIng(3, 1);
		SetCrIng(8, 1);
		break;
	case 9:
		SetCrIng(8, 8);
		break;
	case 10:
		SetCrIng(8, 8);
		break;
	case 11:
		SetCrIng(7, 3);
		break;
	case 12:
		SetCrIng(7, 5);
		break;
	case 13:
		SetCrIng(7, 4);
		break;
	case 14:
		SetCrIng(7, 3);
		break;
	case 23:
		SetCrIng(10, 1);
		SetCrIng(29, 4);
		SetCrIng(30, 8);
		break;
	case 24:
		SetCrIng(8, 10);
		break;
	case 25:
		SetCrIng(20, 1);
		SetCrIng(8, 10);
		break;
	case 26:
		SetCrIng(8, 10);
		SetCrIng(7, 2);
		break;
	case 36:
		SetCrIng(35, 1);
		SetCrIng(32, 1);
		break;
	case 37:
		SetCrIng(8, 5);
		break;
	case 39:
		SetCrIng(38, 1);
		SetCrIng(33, 3);
		break;
	}
}

int prtcr()
{
	int no = 0, num[15], maxa[15];
	for (int i = 1; i < itmid; i++)
	{
		CrReset();
		if (!IsCraftable(i))
		{
			continue;
		}
		CrGetIng(i);
		if ((maxa[no] = GetCrMaxa()) > 0)
		{
			num[no] = i;
			printf("%d.%s\n", ++no, GetItemNm(i));
			for (int j = 0; j < maxi; j++)
			{
				if (Iid[j])
				{
					printf("%s x%2d  ", GetItemNm(Iid[j]), Iamt[j]);
				}
			}
			printf("\n");
		}
	}
	if (!no)
	{
		printf("There' s nothing you can craft.\n");
		return 0;
	}
	printf("Enter number to select, or 0 to cancel.\n");
	int tmpc = InputNum(no);
	if (tmpc == 0)
	{
		return 0;
	}
	printf("Enter amount(max %d), or 0 to cancel.\n", maxa[tmpc - 1]);
	int namt = InputNum(maxa[tmpc - 1]);
	if (namt == 0)
	{
		return 0;
	}
	CrReset();
	CrGetIng(num[tmpc - 1]);
	CraftItem(num[tmpc - 1], namt);
	Refresh();
	return 1;
}

void CrReset()
{
	for (int i = 0; i < maxi; i++)
	{
		Iid[i] = 0;
		Iamt[i] = 0;
	}
	cing = 0;
}

void SetCrIng(int id, int amt)
{
	Iid[cing] = id;
	Iamt[cing] = amt;
	cing++;
}

int GetCrMaxa()
{
	int cmax = player.GetInvAmt(Iid[0]) / Iamt[0];
	if (cmax == 0)
	{
		return 0;
	}
	for (int i = 1; i < cing; i++)
	{
		int tamt = player.GetInvAmt(Iid[i]) / Iamt[i];
		if (tamt == 0)
		{
			return 0;
		}
		if (tamt < cmax)
		{
			cmax = tamt;
		}
	}
	return cmax;
}

void CraftItem(int obid, int amt)
{
	for (int i = 0; i < cing; i++)
	{
		player.DecInv(Iid[i], Iamt[i] * amt);
	}
	player.AddInv(obid, amt, 0, 0);
	tm.Adj(5 * amt, 0, 0);
}