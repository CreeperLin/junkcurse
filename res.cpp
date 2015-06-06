#include "main.h"
using namespace std;
const char *GetBuffNm(int id)
{
	switch (id)
	{
	case 1:
		return "On Fire";
	case 2:
		return "Regeneration";
	case 3:
		return "Poisoned";
	default:
		return "Unknown Buff";
	}
}

int GetEraStart(int era)
{
	switch (era)
	{
	case 0:
		return 0;
	case 1:
		return 30;
	case 2:
		return 50;
	case 3:
		return 1000;
	}
	return 0;
}

const char *GetMobNm(int id)
{
	switch (id)
	{
	case 1:
		return "Hare";
	case 2:
		return "Chicken";
	case 3:
		return "Fish";
	case 4:
		return "Viper";
	case 5:
		return "Wolf";
	case 6:
		return "Bear";
	case 7:
		return "Hawk";
	case 8:
		return "Chomper";
	case 9:
		return "Mummy";
	case 10:
		return "Shadow";
	case 11:
		return "Dryad";
	case 12:
		return "Zombie";
	case 13:
		return "Alien' s sauce";
	case 14:
		return "Hunter";
	case 15:
		return "Caveman with axe";
	case 16:
		return "Caveman with spear";
	case 17:
		return "Caveman Elder";
	case 18:
		return "Shepherd";
	case 19:
		return "Vampire";
	case 20:
		return "Testification1";
	case 21:
		return "Testification2";
	case 22:
		return "Testification3";
	default:
		return "Missing No.";
	}
}

int GetMobInitSte(int id)
{
	switch (id)
	{
	case 4:
	case 5:
	case 6:
	case 8:
	case 9:
	case 10:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 19:
		return 3;
		break;
	default:
		return 1;
	}
}

int GetMobEraS(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		return 0;
	case 20:
	case 21:
	case 22:
		return 1;
	}
	return 7;
}

int GetMobEraE(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 20:
	case 21:
	case 22:
		return 3;
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		return 1;
	}
	return -1;
}

int GetMobRarity(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 5:
	case 15:
	case 16:
	case 17:
	case 18:
	case 20:
	case 21:
	case 22:
		return 1;
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 14:
	case 19:
		return 2;
	}
	return 0;
}

int GetMobBuff(int id)
{
	switch (id)
	{
	case 4:
		return 3;
	}
	return 0;
}

int GetMobBuffP(int id)
{
	switch (id)
	{
	case 4:
		return 15;
	}
	return 0;
}

int GetMobBuffD(int id)
{
	switch (id)
	{
	case 4:
		return 5;
	}
	return 0;
}

int GetMobMhlth(int id)
{
	switch (id)
	{
	case 1:
		return 5;
	case 2:
		return 5;
	case 3:
		return 5;
	case 4:
		return 55;
	case 5:
		return 35;
	case 6:
		return 150;
	case 7:
		return 25;
	case 8:
		return 30;
	case 9:
		return 90;
	case 10:
		return 50;
	case 11:
		return 120;
	case 12:
		return 40;
	case 13:
		return 500;
	case 14:
		return 100;
	case 15:
		return 120;
	case 16:
		return 100;
	case 17:
		return 150;
	case 18:
		return 45;
	case 19:
		return 120;
	case 20:
		return 45;
	case 21:
		return 45;
	case 22:
		return 45;
	}
	return 0;
}

int GetMobMatk(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 13:
	case 18:
		return 0;
	case 4:
		return 8;
	case 5:
		return 10;
	case 6:
		return 25;
	case 7:
		return 15;
	case 8:
		return 40;
	case 9:
		return 20;
	case 10:
		return 10;
	case 11:
		return 25;
	case 12:
		return 10;
	case 14:
		return 15;
	case 15:
		return 15;
	case 16:
		return 10;
	case 17:
		return 20;
	case 19:
		return 20;
	}
	return 0;
}

int GetMobRatk(int id)
{
	switch (id)
	{
	case 13:
		return 50;
	case 14:
		return 10;
	default:
		return 0;
	}
}

int GetMobDef(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
		return 0;
	case 4:
		return 2;
	case 5:
		return 2;
	case 6:
		return 5;
	case 7:
		return 2;
	case 8:
		return 2;
	case 9:
		return 5;
	case 10:
		return 2;
	case 11:
		return 5;
	case 12:
		return 1;
	case 13:
		return 10;
	case 14:
		return 5;
	case 15:
		return 5;
	case 16:
		return 5;
	case 17:
		return 8;
	case 18:
		return 2;
	case 19:
		return 3;
	case 20:
		return 2;
	case 21:
		return 2;
	case 22:
		return 2;
	}
	return 0;
}

int GetMobRng(int id)
{
	switch (id)
	{
	case 11:
		return 4;
	case 13:
		return 9;
	case 14:
		return 16;
	default:
		return 2;
	}
}

int GetMobSrng(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 5:
		return 9;
	case 8:
		return 2;
	case 12:
	case 19:
		return 25;
	default:
		return 16;
	}
}

int GetMobSpd(int id)
{
	switch (id)
	{
	case 6:
		return 1;
	case 5:
	case 10:
	case 11:
	case 12:
		return 2;
	case 8:
		return 0;
	case 13:
	case 19:
		return 3;
	default:
		return 1;
	}
}

int GetMobAtt(int id)
{
	switch (id)
	{
	case 13:
		return 30;
	default:
		return 0;
	}
}

int GetMobSize(int id)
{
	switch (id)
	{
	case 0:
		return 0;
	case 11:
	case 14:
		return 2;
	case 13:
		return 5;
	default:
		return 1;
	}
}

const char *GetMobQuotation(int id, int num)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
		switch (num)
		{
		case 0:
			return ":-D";
		case 1:
			return ":-)";
		case 2:
			return ":-O";
		case 3:
			return ">_<";
		}
		break;
	case 11:
		switch (num)
		{
		case 0:
			return "You'll be punished.";
		case 1:
			return "You don't know what pain really is,do you?";
		case 2:
			return "Step away!";
			case 3;
			return "You don't wanna get hurt,do you?";
		case 4:
			return "You don't belong here,Stranger.";
		case 5:
			return "Aren't you afraid of the dark?";
		case 6:
			return "How did you find me?";
		case 7:
			return "I made these myself.";
		case 8:
			return "Wanna try the spine?";
		case 9:
			return "You look just like those living in caves.";
		case 10:
			return "Nothing can ever destroy the jungle.";
		}
		break;
	case 14:
		switch (num)
		{
		case 0:
			return "Your bow looks familar...";
		case 1:
			return "I'm gonna shoot your head.";
		case 2:
		return "How dare you!" case 3:
			return "Shh...";
		case 4:
			return "That's dinner!";
		case 5:
			return "Hey! Stop messing around in my forest!";
		case 6:
			return "Stay in my hut through the night if you like.";
		case 7:
			return "Better go hunting before dark.";
		case 8:
			return "Here's all I've got.";
		case 9:
			return "I can sell you everything I have except this bow.";
		case 10:
			return "Try not to lose your life in the forest.";
		case 11:
			return "There's a mystery in the jungle.";
		}
		break;
	case 15:
	case 16:
	case 17:
		{
			char tmp[16];
			for (int i = 0; i < randr(8, 16); i++)
			{
				tmp[i] = randr(64, 122);
			}
			return tmp;
			break;
		}
	case 18:
		switch (num)
		{
		case 0:
			return "You shall burn.";
		case 1:
			return "Why harm us?";
		case 2:
			return "We're shepherds, living on the plain.";
		case 3:
			return "Welcome to our shed for a rest.";
		case 4:
			return "You look exhausted,have a gulp of our milk!";
		case 0:
			return "We have wool, but we don't know how to sew.";
		case 1:
			return "Try these cheese!";
		case 0:
			return "Hope you enjoy our milk.";
		case 1:
			return "Some of us have gone hunting and never return.";
		case 2:
			return "Those Cavemen, have a kind of precious gem which was robbed from us.";
		}
		break;
	case 20:
		switch (num)
		{
		case 0:
			return "Ouch! What's wrong with you.";
		case 1:
			return "Ahh... Stay away from me!";
		case 2:
			return "We live together, for safety.";
		case 3:
			return "Welcone to our...village?";
		case 4:
			return "I used to be a shepherd, but I grow corn for a living now.";
		case 5:
			return "Some guys here make nice weapons.";
		case 6:
			return "Some guys here are good at crafting.";
		case 7:
			return "You can host in my house for as long as I'm alive.";
		}
		break;
	case 21:
		switch (num)
		{
		case 0:
			return "Hey!";
		case 1:
			return "Stop it!";
		case 2:
			return "My dad taught me crafting, and I love it.";
		case 3:
			return "I'm a Craftsman, selling hand-made stuff.";
		case 4:
			return "Are you looking for some handy stuff?";
		case 5:
			return "These are all made out of wood.";
		case 6:
			return "Buy this Crossbow if you want to be a Ranger.";
		case 7:
			return "I can teach you to craft your bow into crossbow.";
		case 8:
			return "Go meet the blacksmith if you'd like to get armored.";
		case 9:
			return "I have run out of wood, I wonder if you have some.";
		}
		break;
	default:
		return "...";
	}
}

const char *GetMobQuote(int id, int sit)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
		switch (ste)
		{
		case 1:
		case 2:
			return GetMobQuotation(1, rand() % 3);
		case 4:
			return GetMobQuotation(1, 3);
		}
		break;
	case 14:
		switch (sit)
		{
		case 0:
			if (tgt == -1)
			{
				return GetMobQuotation(14, 1 + rand() % 2);
			}
			else if (tgt > 0)
			{
			return GetMobQuotation(14, 3 + rand() % 2)}
			else
			{
				if (player.IsGrab(21))
				{
					return GetMobQuotation(14, 0);
				}
				return GetMobQuotation(14, 5 + rand() % 3);
			}
		case 1:
			return GetMobQuotation(14, 8 + rand() % 2);
		case 2:
			return GetMobQuotation(14, 10 + rand() % 2);
		}
		break;
	case 11:
		return "(silenced)";
	case 18:
		return "(silenced)";
	case 15:
	case 16:
	case 17:
		return GetMobQuotation(15, 0);
	default:
		return "...";
		return 0;
	}
}

int GetDm(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 13:
		return 0;
	case 4:
		return 15;
	case 5:
		return 10;
	case 6:
		return 20;
	case 7:
		return 15;
	case 8:
		return 50;
	case 9:
		return 60;
	case 10:
		return 40;
	case 11:
		return 30;
	case 12:
		return 5;
	case 14:
		return 20;
	case 15:
		return 10;
	case 16:
		return 10;
	case 17:
		return 20;
	case 18:
		return 5;
	case 20:
		return 5;
	case 21:
		return 5;
	case 22:
		return 5;
	}
	return 0;
}

int GetDmt(int id)
{
	switch (id)
	{
	case 4:
	case 6:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		return 22;
	case 5:
	case 7:
	case 8:
	case 9:
	case 10:
	case 20:
	case 21:
	case 22:
		return 18;
	}
	return 0;
}

int GetDe(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
		return 5;
	case 4:
		return 75;
	case 5:
		return 20;
	case 6:
		return 80;
	case 7:
		return 20;
	case 8:
		return 50;
	case 9:
		return 80;
	case 10:
		return 40;
	case 11:
		return 150;
	case 12:
		return 20;
	case 13:
		return 500;
	case 14:
		return 120;
	case 15:
		return 100;
	case 16:
		return 100;
	case 17:
		return 150;
	case 18:
		return 10;
	case 19:
		return 140;
	case 20:
		return 10;
	case 21:
		return 10;
	case 22:
		return 10;
	}
	return 0;
}

const char *GetBlkNm(int id)
{
	switch (id)
	{
	case 0:
		return "dirt";
	case 1:
		return "grassland";
	case 2:
		return "forest";
	case 3:
		return "deep water";
	case 4:
		return "shallow water";
	case 5:
		return "mountain";
	case 6:
		return "peak";
	case 7:
		return "sand";
	case 8:
		return "jungle";
	case 9:
		return "bush";
	case 10:
		return "swamp";
	case 11:
		return "hut";
	case 12:
		return "cave";
	case 13:
		return "cavewall";
	case 14:
		return "shed";
	case 15:
		return "path";
	case 16:
		return "house";
	default:
		return "field";
	}
}

int GetItemMxstk(int id)
{
	switch (id)
	{
	case -1:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 21:
	case 23:
	case 24:
	case 25:
	case 26:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 43:
	case 44:
		return 1;
	case 18:
	case 22:
	case 40:
		return 250;
	default:
		return 64;
	}
}

const char *GetItemNm(int id)
{
	switch (id)
	{
	case -1:
		return "custom item";
	case 1:
		return "Raw Hare Meat";
	case 2:
		return "Raw Chicken";
	case 3:
		return "Raw Fish";
	case 4:
		return "Roast Hare Meat";
	case 5:
		return "Roast Chicken";
	case 6:
		return "Roast Fish";
	case 7:
		return "Hare Fur";
	case 8:
		return "Wood";
	case 9:
		return "Wooden Sword";
	case 10:
		return "Club";
	case 11:
		return "Fur Cap";
	case 12:
		return "Fur Coat";
	case 13:
		return "Fur Legging";
	case 14:
		return "Fur Boot";
	case 15:
		return "Herb";
	case 16:
		return "Apple";
	case 17:
		return "Berry";
	case 18:
		return "Shell";
	case 19:
		return "Arrow";
	case 20:
		return "Torch";
	case 21:
		return "Bow";
	case 22:
		return "Stone";
	case 23:
		return "Mace";
	case 24:
		return "Table";
	case 25:
		return "Campfire";
	case 26:
		return "Tent";
	case 27:
		return "Waterskin";		// -
	case 28:
		return "Waterskin of milk";	// -
	case 29:
		return "Venomous Fang";
	case 30:
		return "Wolf's Fang";
	case 31:
		return "Glowing Orb";
	case 32:
		return "White Pearl";
	case 33:
		return "Black Pearl";
	case 34:
		return "Claw";
	case 35:
		return "Crook";
	case 36:
		return "Magical Crook";
	case 37:
		return "Slingshot";
	case 38:
		return "Stone Axe";
	case 39:
		return "Shade Axe";
	case 40:
		return "Poisoned Spine";
	case 41:
		return "Wool";
	case 42:
		return "Cheese";
	case 43:
		return "Mark I";		// -
	case 44:
		return "Bomb";
	case 45:
		return "Trap";
	case 46:
		return "Crossbow";
	case 47:
		return "Onyx";
	case 48:
		return "Purple Fruit";
	default:
		return "shit";
	}
}

int GetItemValue(int id)
{
	switch (id)
	{
	case 1:
		return 4;
	case 2:
		return 3;
	case 3:
		return 3;
	case 4:
		return 6;
	case 5:
		return 5;
	case 6:
		return 5;
	case 7:
		return 3;
	case 9:
		return 10;
	case 10:
		return 10;
	case 11:
		return 10;
	case 12:
		return 20;
	case 13:
		return 10;
	case 14:
		return 10;
	case 15:
		return 10;
	case 16:
		return 2;
	case 17:
		return 1;
	case 18:
		return 1;
	case 19:
		return 2;
	case 20:
		return 3;
	case 21:
		return 20;
	case 22:
		return 3;
	case 23:
		return 20;
	case 24:
		return 5;
	case 25:
		return 5;
	case 26:
		return 10;
	case 27:
		return 0;				// -
	case 28:
		return 0;				// -
	case 29:
		return 5;
	case 30:
		return 4;
	case 31:
		return 100;
	case 32:
		return 30;
	case 33:
		return 20;
	case 34:
		return 30;
	case 35:
		return 5;
	case 36:
		return 30;
	case 37:
		return 15;
	case 38:
		return 18;
	case 39:
		return 40;
	case 40:
		return 13;
	case 41:
		return 0;
	case 42:
		return 9;
	case 43:
		return 0;				// -
	case 44:
		return 0;				// -
	case 46:
		return 45;
	case 47:
		return 0;
	case 48:
		return 10;
	}
	return 0;
}

int GetItemBuff(int id)
{
	switch (id)
	{
	case 23:
	case 40:
		return 3;
	}
	return 0;
}

int GetItemBuffP(int id)
{
	switch (id)
	{
	case 23:
		return 10;
	case 40:
		return 3;
	}
	return 0;
}

int GetItemBuffD(int id)
{
	switch (id)
	{
	case 23:
	case 40:
		return 5;
	}
	return 0;
}

int GetItemType(int id)
{
	switch (id)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 15:
	case 16:
	case 17:
	case 42:
		return 1;
	case 24:
	case 25:
	case 26:
	case 45:
		return 2;
	case 11:
		return 3;
	case 12:
		return 4;
	case 13:
		return 5;
	case 14:
		return 6;
	case 32:
	case 33:
		return 7;
	case 9:
	case 10:
	case 23:
	case 38:
	case 39:
		return 8;
	case 21:
	case 37:
	case 40:
	case 44:
	case 46:
		return 9;
	case 36:
	case 43:
		return 10;
	case 48:
		return 11;
	default:
		return 0;
	}
}

int GetItemMpc(int id)
{
	switch (id)
	{
	case 36:
		return 4;
	case 43:
		return player.mp;
	}
	return 0;
}

int GetItemAtt(int id)
{
	switch (id)
	{
	case 20:
		return 20;
	}
	return 0;
}

int GetItemDmg(int id)
{
	switch (id)
	{
	case 9:
		return 5;
	case 10:
		return 8;
	case 21:
		return 10;
	case 23:
		return 15;
	case 36:
		return 15;
	case 37:
		return 8;
	case 38:
		return 15;
	case 39:
		return 25;
	case 40:
		return 8;
	case 43:
		return 5 * player.mp;
	case 46:
		return 20;
	}
	return 0;
}

int GetItemDef(int id)
{
	switch (id)
	{
	case 11:
		return 2;
	case 12:
		return 4;
	case 13:
		return 2;
	case 14:
		return 2;
	}
	return 0;
}

int GetItemRng(int id)
{
	switch (id)
	{
	case 9:
	case 10:
	case 23:
	case 38:
	case 39:
		return 2;
	case 21:
	case 44:
		return 16;
	case 36:
	case 37:
	case 40:
	case 43:
		return 9;
	case 46:
		return 25;
	}
	return -1;
}

int GetItemCc(int id)
{
	switch (id)
	{
	case 9:
		return 3;
	case 10:
		return 1;
	case 21:
		return 3;
	case 23:
	case 36:
	case 40:
	case 43:
	case 44:
		return 5;
	case 37:
		return 4;
	case 38:
		return 6;
	case 39:
		return 8;
	case 46:
		return 9;
	}
	return 0;
}

int GetItemFd(int id)
{
	switch (id)
	{
	case 1:
		return 20;
	case 2:
		return 15;
	case 3:
		return 15;
	case 4:
		return 30;
	case 5:
		return 25;
	case 6:
		return 25;
	case 15:
		return 50;
	case 16:
		return 10;
	case 17:
		return 5;
	case 42:
		return 45;
	}
	return 0;
}

int GetItemFm(int id)
{
	switch (id)
	{
	case 48:
		return 50;
	}
	return 0;
}

int GetItemAdmg(int id)
{
	switch (id)
	{
	case 19:
		return 3;
	case 22:
		return 2;
	}
	return 0;
}

int GetAmmoType(int wid)
{
	switch (wid)
	{
	case 21:
	case 46:
		return 19;
	case 37:
		return 22;
	case 40:
	case 44:
		return wid;
	}
	return 0;
}

int GetExRng(int id)
{
	switch (id)
	{
	case 31:
		return 200;
	case 44:
		return 3;
	}
	return 0;
}

int GetExDmg(int id)
{
	switch (id)
	{
	case 31:
		return 1000;
	case 44:
		return 60;
	}
	return 0;
}