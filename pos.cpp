#include "pos.h"
#include "def.h"
using namespace std;
extern unsigned long int blki(int x, int y);
void pos::move(int dir, int spd)
{
	x += dtox(dir) * spd;
	y += dtoy(dir) * spd;
}

void pos::operator=(pos p)
{
	this->x = p.x;
	this->y = p.y;
}

int pos::operator==(pos p)
{
	if (this->x == p.x && this->y == p.y)
	{
		return 1;
	}
	return 0;
}

int pos::operator!=(pos p)
{
	if (this->x == p.x && this->y == p.y)
	{
		return 0;
	}
	return 1;
}

unsigned int pos::operator+(pos p)
{
	int tmp1 = this->x - p.x;
	int tmp2 = this->y - p.y;
	return tmp1 * tmp1 + tmp2 * tmp2;
}

void pos::Reset()
{
	x = 0;
	y = 0;
}

void pos::Set(int nx, int ny)
{
	x = nx;
	y = ny;
}

unsigned long int pos::geti()
{
	return blki(x,y);
}

pos ctop(unsigned int nx, unsigned int ny)
{
	pos p;
	p.x = nx;
	p.y = ny;
	return p;
}

int GetDir(pos p1, pos p2)
{
	if (p1.x < p2.x)
	{
		if (p1.y < p2.y)
		{
			return 4;
		}
		else if (p1.y == p2.y)
		{
			return 3;
		}
		else if (p1.y > p2.y)
		{
			return 2;
		}
	}
	else if (p1.x == p2.x)
	{
		if (p1.y < p2.y)
		{
			return 5;
		}
		else if (p1.y == p2.y)
		{
			return 0;
		}
		else if (p1.y > p2.y)
		{
			return 1;
		}
	}
	else if (p1.x > p2.x)
	{
		if (p1.y < p2.y)
		{
			return 6;
		}
		else if (p1.y == p2.y)
		{
			return 7;
		}
		else if (p1.y > p2.y)
		{
			return 8;
		}
	}
}

int dtox(int d)
{
	switch (d)
	{
	case 1:
	case 5:
		return 0;
		break;
	case 2:
	case 3:
	case 4:
		return 1;
		break;
	case 6:
	case 7:
	case 8:
		return -1;
		break;
	default:
		return 0;
	}
}

int dtoy(int d)
{
	switch (d)
	{
	case 3:
	case 7:
		return 0;
		break;
	case 4:
	case 5:
	case 6:
		return 1;
		break;
	case 1:
	case 2:
	case 8:
		return -1;
		break;
	default:
		return 0;
	}
}

const char *GetDirNm(int dir)
{
	switch (dir)
	{
	case 1:
		return "north";
		break;
	case 2:
		return "northeast";
		break;
	case 3:
		return "east";
		break;
	case 4:
		return "southeast";
		break;
	case 5:
		return "south";
		break;
	case 6:
		return "southwest";
		break;
	case 7:
		return "west";
		break;
	case 8:
		return "northwest";
		break;
	default:
		return "head";
		break;
	}
}