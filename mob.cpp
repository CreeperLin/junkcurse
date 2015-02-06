#include "main.h"
using namespace std;
int maxspn;
int spnrt;
int tolspn;
int IsFriend(int id, int oid)
{
	if (id == oid)
	{
		return 1;
	}
	switch (id)
	{
	}
}

int IsInfect(int id, int oid)
{
	switch (id)
	{
	case 12:
	case 19:
		switch (oid)
		{
		case 14:
		case 18:
		case 20:
			return 1;
		}
	}
	return 0;
}

int CMob::FindMob(int nid)
{
	for (int i = 0; i < mobn; i++)
	{
		if (i != sbj - 1 && mob[i].id == nid && p + mob[i].p <= GetSrng()
			&& !IsColls(p, mob[i].p))
		{
			return i + 1;
		}
	}
	return 0;
}

void CMob::Atk(int obj, int dt)
{
	int tma, tcc;
	if (dt == 1)
	{
		tma = GetMatk();
		tcc = GetMcc();
	}
	else
	{
		tma = GetRatk();
		tcc = GetRcc();
	}
	int bid = GetMobBuff(id);
	if (bid && Prob(GetMobBuffP(id)))
	{
		if (obj == -1)
		{
			player.Addbuff(bid, GetMobBuffD(id), id);
		}
		else
		{
			mob[obj - 1].Addbuff(bid, GetMobBuffD(id), id);
		}
	}
	if (obj == -1)
	{
		player.Adjhlth(AtkCnt(tma, player.GetDef(), tcc), 1, id);
	}
	else
	{
		for (int i = 0; i < mobn; i++)
		{
			if (i != sbj - 1 && i != tgt - 1 && mob[i].id == mob[tgt - 1].id
				&& p + mob[i].p <= mob[i].GetSrng() && !IsColls(p, mob[i].p))
			{
				mob[i].AIFb(2, sbj);
			}
		}
		if (mob[tgt - 1].Adjhlth
			(AtkCnt(tma, mob[tgt - 1].GetDef(), tcc), 1, id))
		{
			int oid = mob[tgt - 1].id, num = mob[tgt - 1].sbj;
			pos np = mob[tgt - 1].p;
			mob[tgt - 1].Reset();
			if (IsInfect(id, oid))
			{
				mob[num - 1].Spawn(12, num, np);
			}
			tgt = 0;
			return;
		}
		if (p + mob[tgt - 1].p <= mob[tgt - 1].GetSrng() + GetAtt())
		{
			mob[tgt - 1].AIFb(1, sbj);
		}
	}
}

int CMob::SlctTgt()
{
	int ntgt[10];
	int cnum = 0;
	switch (id)
	{
	case 4:
		ntgt[cnum++] = -1;
		ntgt[cnum++] = 14;
		ntgt[cnum++] = 18;
		ntgt[cnum++] = 20;
		break;
	case 5:
		ntgt[cnum++] = 1;
		ntgt[cnum++] = 2;
		break;
	case 6:
		ntgt[cnum++] = 3;
		break;
	case 8:
		ntgt[cnum++] = -1;
		ntgt[cnum++] = 1;
		ntgt[cnum++] = 2;
		ntgt[cnum++] = 5;
		ntgt[cnum++] = 14;
		ntgt[cnum++] = 18;
		ntgt[cnum++] = 20;
		break;
	case 9:
		ntgt[cnum++] = -1;
		break;
	case 10:
		ntgt[cnum++] = -1;
		break;
	case 12:
		ntgt[cnum++] = -1;
		ntgt[cnum++] = 14;
		ntgt[cnum++] = 18;
		ntgt[cnum++] = 20;
		break;
	case 13:
		ntgt[cnum++] = -1;
		ntgt[cnum++] = 14;
		ntgt[cnum++] = 18;
		ntgt[cnum++] = 20;
		break;
	case 14:
		ntgt[cnum++] = 1;
		ntgt[cnum++] = 2;
		ntgt[cnum++] = 4;
		ntgt[cnum++] = 5;
		ntgt[cnum++] = 12;
		ntgt[cnum++] = 19;
		break;
	case 15:
		ntgt[cnum++] = -1;
		break;
	case 16:
		ntgt[cnum++] = -1;
		break;
	case 17:
		ntgt[cnum++] = -1;
		break;
	case 19:
		ntgt[cnum++] = -1;
		ntgt[cnum++] = 14;
		ntgt[cnum++] = 18;
		ntgt[cnum++] = 20;
		break;
	default:
		return 0;
	}
	for (int i = 0; i < cnum; i++)
	{
		switch (ntgt[i])
		{
		case -1:
			if (player.health > 0
				&& player.p + p <= GetSrng() + player.GetAtt()
				&& !IsColls(p, player.p))
			{
				tgt = player.IsEquipped(31) ? 0 : -1;
			}
			break;
		default:
			tgt = FindMob(ntgt[i]);
		}
		if (tgt != 0)
		{
			ste = 3;
			for (int i = 0; i < mobn; i++)
			{
				if (i != sbj - 1 && id == mob[i].id
					&& p + mob[i].p <= mob[i].GetSrng()
					&& !IsColls(p, mob[i].p))
				{
					mob[i].AIFb(2, tgt);
				}
			}
			return 1;
		}
	}
	return 0;
}

void CMob::Mmove(int dir)
{
	if (!dir)
	{
		dir = randr(1, 8);
	}
	if (IsCollm(id, p, dir))
	{
		for (int i = 0; i < 7; i++)
		{
			dir++;
			if (dir > 8)
			{
				dir -= 8;
			}
			if (!IsCollm(id, p, dir))
			{
				break;
			}
		}
	}
	int mspd = GetSpd();
	while (mspd > 0 && !IsCollm(id, p, dir))
	{
		p.move(dir, 1);
		mspd--;
	}
}

void CMob::Mmove(pos op)
{
	int dir = GetDir(p, op);
	if (!dir)
	{
		return;
	}
	if (IsCollm(id, p, dir))
	{
		for (int i = 0; i < 7; i++)
		{
			dir++;
			if (dir > 8)
			{
				dir -= 8;
			}
			if (!IsCollm(id, p, dir))
			{
				break;
			}
		}
	}
	int mspd = GetSpd();
	int rng = GetRng();
	while (mspd > 0 && !IsCollm(id, p, dir) && p + op > rng)
	{
		p.move(dir, 1);
		mspd--;
	}
}

void CMob::AIFb(int msg, int tag)
{
	switch (msg)
	{
	case 1:
		tgt = tag;
		switch (id)
		{
		case 1:
		case 2:
		case 3:
			if (Prob(30))
			{
				ste = 4;
			}
			break;
		case 18:
		case 20:
			ste = 4;
			break;
		default:
			ste = 3;
			break;
		}
		break;
	case 2:
		tgt = tag;
		switch (id)
		{
		case 1:
		case 2:
		case 3:
		case 18:
		case 20:
			if (Prob(30))
			{
				ste = 4;
			}
			break;
		default:
			ste = 3;
			for (int i = 0; i < mobn; i++)
			{
				if (i != sbj - 1 && id == mob[i].id && mob[i].tgt != tgt
					&& p + mob[i].p <= mob[i].GetSrng()
					&& !IsColls(p, mob[i].p))
				{
					mob[i].AIFb(2, tgt);
				}
			}
			break;
		}
	}
}

void CMob::AIAct()
{
	if (tgt == -1)
	{
		if (player.health <= 0)
		{
			tgt = 0;
		}
	}
	else if (tgt > -1)
	{
		if (mob[tgt - 1].health <= 0)
		{
			tgt = 0;
		}
	}
	switch (ste)
	{
	case 1:
		return;
	case 2:
		Mmove(randr(1, 8));
		break;
	case 3:
		{
			pos op;
			int oatt = 0, ospd = 0;
			if (!tgt)
			{
				if (!SlctTgt())
				{
					break;
				}
			}
			if (tgt == -1)
			{
				op = player.p;
				oatt = player.GetAtt();
				ospd = player.GetSpd();
			}
			else if (tgt > 0)
			{
				op = mob[tgt - 1].p;
				oatt = mob[tgt - 1].GetAtt();
				ospd = mob[tgt].ste == 1 ? 0 : mob[tgt - 1].GetSpd();
			}
			int dist = p + op, rng = GetRng();
			if (dist <= rng && !IsColls(p, op))
			{
				int tdt;
				if (rng == 2)
				{
					tdt = 1;
				}
				else
				{
					if (GetMatk() >= GetRatk() && dist <= 2)
					{
						tdt = 1;
					}
					else
					{
						tdt = 2;
					}
				}
				Atk(tgt, tdt);
			}
			else
			{
				pos ep = op;
				if (ospd)
				{
					ep.move(GetDir(p, op), ospd);
				}
				Mmove(ep);
				if (dist > GetSrng() + oatt || IsColls(p, op))
				{
					lst--;
					if (lst <= 0)
					{
						tgt = 0;
						lst = 3;
					}
				}
				else
				{
					lst = 3;
				}
			}
			break;
		}
	case 4:
		{
			int fdir;
			pos fp;
			if (tgt == -1)
			{
				fp = player.p;
			}
			else if (tgt == 0)
			{
				fdir = randr(1, 8);
				Mmove(fdir);
				break;
			}
			else if (tgt > 0)
			{
				fp = mob[tgt - 1].p;
			}
			fdir = GetDir(fp, p);
			Mmove(fdir);
			int dist = p + fp;
			if (dist > GetSrng())
			{
				lst--;
				if (lst <= 0)
				{
					lst = 3;
					ste = 1;
				}
			}
			else
			{
				lst = 3;
			}
			break;
		}
	}
}

int CMob::GetMhlth()
{
	int tmp = GetMobMhlth(id);
	return tmp;
}

int CMob::GetMatk()
{
	int tmp = GetMobMatk(id);
	return tmp;
}

int CMob::GetRatk()
{
	int tmp = GetMobRatk(id);
	return tmp;
}

int CMob::GetDef()
{
	int tmp = GetMobDef(id);
	return tmp;
}

int CMob::GetRng()
{
	int tmp = GetMobRng(id);
	return tmp;
}

int CMob::GetSrng()
{
	int tmp = GetMobSrng(id);
	return tmp;
}

int CMob::GetSpd()
{
	int tmp = GetMobSpd(id);
	return tmp;
}

int CMob::GetMcc()
{
	return 3;
}

int CMob::GetRcc()
{
	return 3;
}

int CMob::GetAtt()
{
	int tmp = GetMobAtt(id);
	return tmp;
}

const char *CMob::name()
{
	return GetMobNm(id);
}

int CMob::GetSize()
{
	return GetMobSize(id);
}

void CMob::Spawn(int tid, int num, pos sp)
{
	id = tid;
	sbj = num;
	p = sp;
	health = maxhlth = GetMhlth();
	ste = GetMobInitSte(id);
	lst = 3;
	tolspn += GetSize();
	//msg.print("A %s has spawned", name());
}

int CMob::Speak(int sit)
{
	msg.print("%s: ", name());
	switch (id)
	{
	case 1:
	case 2:
	case 3:
		switch (ste)
		{
		case 1:
		case 2:
			switch (rand() % 3)
			{
			case 0:
				msg.print(":-D");
				break;
			case 1:
				msg.print(":-)");
				break;
			case 2:
				msg.print(":-O");
				break;
			}
			break;
		case 4:
			msg.print(">_<");
		}
		break;
	case 14:
		switch (sit)
		{
		case 0:
			if (player.IsGrab(21))
			{
				msg.print("Your bow looks familar...");
				return 1;
			}
			if (tgt == -1)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("I'm gonna shoot your head.");
					break;
				case 1:
					msg.print("How dare you!");
					break;
				}
				return 0;
			}
			else if (tgt > 0)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("Shh...");
					break;
				case 1:
					msg.print("That's dinner!");
					break;
				}
				return 0;
			}
			else
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("Hey! Stop messing around in my forest!");
					break;
				case 1:
					if (tm.IsNt())
					{
						msg.print
							("Stay in my hut through the night if you like.");
					}
					else
					{
						msg.print("Better go hunting before dark.");
					}
					break;
				}
				return 1;
			}
			break;
		case 1:
			switch (rand() % 2)
			{
			case 0:
				msg.print("Here's all I've got.");
				break;
			case 1:
				msg.print("I can sell you everything I have except this bow.");
				break;
			}
			break;
		case 2:
			switch (rand() % 2)
			{
			case 0:
				msg.print("Try not to lose your life in the forest.");
				break;
			case 1:
				msg.print("There's a mystery in the jungle.");
				break;
			}
			break;
		}
		break;
	case 11:
		switch (sit)
		{
		case 0:
			if (tgt == -1)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("You'll be punished.");
					break;
				case 1:
					msg.print("You don't know what pain really is,do you?");
					break;
				}
				return 0;
			}
			else if (tgt > 0)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("Step away!");
					break;
				case 1:
					msg.print("You don't wanna get hurt,do you?");
					break;
				}
				return 1;
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					msg.print("You don't belong here,Stranger.");
					break;
				case 1:
					msg.print("Aren't you afraid of the dark?");
					break;
				case 2:
					msg.print("How did you find me?");
					break;
				}
				return 1;
			}
			break;
		case 1:
			switch (rand() % 2)
			{
			case 0:
				msg.print("I made these myself.");
				break;
			case 1:
				msg.print("Wanna try the spine?");
				break;
			}
			break;
		case 2:
			switch (rand() % 2)
			{
			case 0:
				msg.print("You look just like those living in caves.");
				break;
			case 1:
				msg.print("Nothing can ever destroy the jungle.");
				break;
			}
			break;
		}
		break;
	case 18:
		switch (sit)
		{
		case 0:
			if (tgt == -1)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("You should burn.");
					break;
				case 1:
					msg.print("Why harm us?");
					break;
				}
				return 0;
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					msg.print("We're shepherds, living on the plain.");
					break;
				case 1:
					msg.print("Welcome to our shed for a rest.");
					break;
				case 2:
					msg.print("You look exhausted,have a gulp of our milk!");
					break;
				}
				return 1;
			}
			break;
		case 1:
			switch (rand() % 2)
			{
			case 0:
				msg.print("We have wool, but we don't know how to sew.");
				break;
			case 1:
				msg.print("Try these cheese!");
				break;
			}
			break;
		case 2:
			switch (rand() % 3)
			{
			case 0:
				msg.print("Hope you enjoy our milk.");
				break;
			case 1:
				msg.print("Some of us have gone hunting and never return.");
				break;
			case 2:
				msg.print
					("Those Cavemen, have a kind of precious gem which was robbed from us.");
				break;
			}
			break;
		}
		break;
	case 15:
	case 16:
	case 17:
		for (int i = 0; i < randr(8, 16); i++)
		{
			putchar(randr(64, 122));
		}
		putchar('\n');
		break;
	case 20:
		switch (sit)
		{
		case 0:
			if (tgt == -1)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("Ouch! What's wrong with you.");
					break;
				case 1:
					msg.print("Ahh... Stay away from me!");
					break;
				}
				return 0;
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					msg.print("We live together, for safety.");
					break;
				case 1:
					msg.print("Welcone to our...village?");
					break;
				case 2:
					msg.print
						("I used to be a shepherd, but I grow corn for a living now.");
					break;
				}
				return 0;
			}
			break;
		case 2:
			switch (rand() % 3)
			{
			case 0:
				msg.print("Some guys here make nice weapons.");
				break;
			case 1:
				msg.print("Some guys here are good at crafting.");
				break;
			case 2:
				msg.print("You can host in my house for as long as I'm alive.");
				break;
			}
			break;
		}
		break;
	case 21:
		switch (sit)
		{
		case 0:
			if (tgt == -1)
			{
				switch (rand() % 2)
				{
				case 0:
					msg.print("Hey!");
					break;
				case 1:
					msg.print("Stop it!");
					break;
				}
				return 0;
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					msg.print("My dad taught me crafting, and I love it.");
					break;
				case 1:
					msg.print("I'm a Craftsman, selling hand-made stuff.");
					break;
				case 2:
					msg.print("Are you looking for some handy stuff?");
					break;
				}
				return 1;
			}
			break;
		case 1:
			switch (rand() % 2)
			{
			case 0:
				msg.print("These are all made out of wood.");
				break;
			case 1:
				msg.print("Buy this Crossbow if you want to be a Ranger.");
				break;
			}
			break;
		case 2:
			switch (rand() % 3)
			{
			case 0:
				msg.print("I can teach you to craft your bow into crossbow.");
				break;
			case 1:
				msg.print
					("Go meet the blacksmith if you'd like to get armored.");
				break;
			case 2:
				msg.print("I have run out of wood, I wonder if you have some.");
				break;
			}
			break;
		}
		break;
	default:
		msg.print("...");
		return 0;
	}
	return 0;
}

void CMob::Reset()
{
	if (sbj == player.ptgt)
	{
		player.ptgt = 0;
	}
	for (int i = 0; i < mobn; i++)
	{
		if (sbj == mob[i].tgt)
		{
			mob[i].tgt = 0;
		}
	}
	tolspn -= GetSize();
	Wipebuff();
	id = 0;
	sbj = 0;
	lvl = 0;
	tgt = 0;
	ste = 0;
	lst = 0;
	health = 0;
	maxhlth = 0;
	p.Reset();
}

void MobSpawn()
{
	int cap = maxspn - tolspn;
	if (cap > 0 && Prob(spnrt))
	{
		pos sp;
		int st = 0, tl = 7, plsrng = player.GetSrng();
		while (1)
		{
			int tx = randr(player.p.x - tl, player.p.x + tl);
			int ty = randr(player.p.y - tl, player.p.y + tl);
			sp = ctop(tx, ty);
			if (tx >= 0 && tx < wlth && ty >= 0 && ty < wlth
				&& sp + player.p > plsrng)
			{
				if (!BlcSlctm(blk[sp.geti()], 0))
				{
					break;
				}
			}
			if (++st >= 100)
			{
				fprintf(stderr, "crashed blk %d %d %d\n", tx, ty,
						blk[blki(tx, ty)]);
				return;
			}
		}
		if (cap > 1 && Prob(100))
		{
			//msg.print("group");
			int trys = 0, tid = 0, cid = blk[sp.geti()], num =
				min(cap, randr(2, 3));
			do
			{
				tid = SlctMob();
				if (++trys >= 100)
				{
					fprintf(stderr, "crashed mob group id %d %d %d\n", sp.x,
							sp.y, blk[sp.geti()]);
					return;
				}
			}
			while (!SpawnChk(tid, cid) || BlcSlctm(cid, tid));
			trys = 0;
			do
			{
				pos cp = sp;
				cp.x += (-1 + 2 * (rand() % 2)) * randr(1, 2);
				cp.y += (-1 + 2 * (rand() % 2)) * randr(1, 2);
				int bid = blk[cp.geti()];
				if (!BlcSlctm(bid, tid) && SpawnChk(tid, bid)
					&& cp + player.p > plsrng)
				{
					SpawnMob(tid, cp);
					num--;
				}
				else if (++trys >= 100)
				{
					fprintf(stderr, "crashed mob group %d %d %d\n", cp.x, cp.y,
							blk[cp.geti()]);
					num--;
				}
			}
			while (num > 0);
			return;
		}
		st = 0;
		while (1)
		{
			int tid = SlctMob();
			int bid = blk[sp.geti()];
			if (!BlcSlctm(bid, tid) && SpawnChk(tid, bid))
			{
				SpawnMob(tid, sp);
				return;
			}
			if (++st >= 100)
			{
				fprintf(stderr, "crashed mob %d %d %d\n", sp.x, sp.y,
						blk[sp.geti()]);
				return;
			}
		}
	}
}

void SpawnMob(int id, pos p)
{
	for (int i = 0; i < mobn; i++)
	{
		if (!mob[i].id)
		{
			mob[i].Spawn(id, i + 1, p);
			return;
		}
	}
}

int SlctMob()
{
	int ord[mobid], on = 0, rar[mobid], rn = 0;
	for (int i = 1; i <= mobid; i++)
	{
		switch (GetMobRarity(i))
		{
		case 1:
			ord[on++] = i;
			break;
		case 2:
			rar[rn++] = i;
			break;
		}
	}
	int pr = rand() % 100;
	if (pr < 90)
	{
		return ord[rand() % on];
	}
	else if (pr < 100)
	{
		return rar[rand() % rn];
	}
	return 0;
}

int SpawnChk(int id, int tid)
{
	if (world.era < GetMobEraS(id) || world.era >= GetMobEraE(id))
	{
		return 0;
	}
	int terr[10], n = 0, tt = 0;
	for (int i = 0; i < 10; i++)
	{
		terr[i] = 0;
	}
	switch (id)
	{
	case 1:
	case 2:
		terr[n++] = 1;
		terr[n++] = 2;
		terr[n++] = 9;
		terr[n++] = 5;
		break;
	case 3:
		terr[n++] = 3;
		terr[n++] = 4;
		break;
	case 4:
		tt = 1;
		terr[n++] = 8;
		terr[n++] = 10;
		break;
	case 5:
		tt = 2;
		terr[n++] = 2;
		terr[n++] = 9;
		terr[n++] = 5;
		terr[n++] = 10;
		break;
	case 6:
		if (tm.GetSe() == 4)
		{
			return 0;
		}
		terr[n++] = 2;
		terr[n++] = 9;
		terr[n++] = 10;
		break;
	case 7:
		tt = 2;
		terr[n++] = 6;
		break;
	case 8:
		terr[n++] = 8;
		break;
	case 9:
		terr[n++] = 7;
		break;
	case 10:
		tt = 2;
		break;
	case 11:
		tt = 2;
		terr[n++] = 8;
		break;
	case 12:
		return 0;
	case 13:
		tt = 2;
		break;
	case 14:
		switch (tid)
		{
		case 11:
			return 1;
		case 2:
		case 9:
			if (!tm.IsNt())
			{
				return 1;
			}
		}
		return 0;
		break;
	case 15:
	case 16:
	case 17:
		terr[n++] = 5;
		terr[n++] = 12;
		break;
	case 18:
		switch (tid)
		{
		case 14:
			return 1;
		case 1:
			if (!tm.IsNt())
			{
				return 1;
			}
		}
		return 0;
		break;
	case 19:
		tt = 2;
		terr[n++] = 1;
		terr[n++] = 2;
		terr[n++] = 9;
		break;
	case 20:
	case 21:
	case 22:
		switch (tid)
		{
		case 16:
			return 1;
		case 1:
		case 15:
			if (!tm.IsNt())
			{
				return 1;
			}
		}
		return 0;
	}
	if (tt && tm.IsNt() != (tt - 1))
	{
		return 0;
	}
	if (!terr[0])
	{
		return 1;
	}
	for (int i = 0; i < n; i++)
	{
		if (tid == terr[i])
		{
			return 1;
		}
	}
	return 0;
}

void SetSpnEnv()
{
	switch (fbio)
	{
	case 0:
		maxspn = 5;
		spnrt = 10;
		break;
	case 1:
		maxspn = 5;
		spnrt = 10;
		break;
	case 2:
		maxspn = 5;
		spnrt = 15;
		break;
	case 3:
		maxspn = 4;
		spnrt = 15;
		break;
	case 4:
		maxspn = 8;
		spnrt = 15;
		break;
	case 5:
		maxspn = 5;
		spnrt = 10;
		break;
	case 6:
		maxspn = 10;
		spnrt = 25;
		break;
	case 7:
		maxspn = 10;
		spnrt = 25;
		break;
	}
	if (tm.IsNt())
	{
		maxspn *= 1.2;
		spnrt *= 1.2;
	}
}

void CMob::Drop()
{
	int did[10], damt[10], dpb[10], n = -1;
	int base = GetDm(id), nexp = GetDe(id), tmny = 0;
	for (int i = 0; i < 10; i++)
	{
		did[i] = damt[i] = dpb[i] = 0;
	}
	switch (id)
	{
	case 1:
		did[++n] = 1, damt[n] = 1;
		did[++n] = 7, damt[n] = randr(0, 1);
		break;
	case 2:
		did[++n] = 2, damt[n] = 1;
		break;
	case 3:
		did[++n] = 3, damt[n] = 1;
		break;
	case 4:
		did[++n] = 29, damt[n] = 1, dpb[n] = 30;
		break;
	case 5:
		did[++n] = 30, damt[n] = randr(1, 3), dpb[n] = 30;
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		did[++n] = 33, damt[n] = 1, dpb[n] = 25;
		break;
	case 11:
		did[++n] = 32, damt[n] = 1;
		break;
	case 12:
		break;
	case 13:
		did[++n] = 31, damt[n] = 1, dpb[n] = 30;
		break;
	case 14:
		did[++n] = 21, damt[n] = 1;
		did[++n] = 19, damt[n] = randr(3, 5);
		did[++n] = 20, damt[n] = randr(0, 1);
		break;
	case 15:
		did[++n] = 38, damt[n] = 1, dpb[n] = 30;
		break;
	case 17:
		did[++n] = 47, damt[n] = 1, dpb[n] = 40;
		break;
	case 18:
		did[++n] = 35, damt[n] = randr(0, 1);
		break;
	}
	for (int i = 0; i <= n; i++)
	{
		if ((!dpb[i]) || Prob(dpb[i]))
		{
			player.AddInv(did[i], damt[i], 0, 0);
		}
	}
	if (base)
	{
		int pb = randr(0, 100);
		if (pb < 20)
		{
			tmny = base * 0.8;
		}
		else if (pb < 40)
		{
			tmny = base * 1.2;
		}
		else if (pb < 80)
		{
			tmny = base * 1.6;
		}
		else
		{
			tmny = base * 2;
		}
		player.AddInv(GetDmt(id), tmny, 0, 0);
	}
	player.AddExp(nexp * (1 + 0.1 * lvl));
}