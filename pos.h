#ifndef _POS_H_
#define _POS_H_
struct pos
{
	int x;
	int y;
	void move(int dir,int spd);
	void operator=(pos p);
	int operator==(pos p);
	int operator!=(pos p);
	unsigned int operator+(pos p);
	unsigned long int geti();
	void Reset();
	void Set(int nx,int ny);
};
int GetDir(pos p1, pos p2);
pos ctop(unsigned int nx, unsigned int ny);
int dtox(int d);
int dtoy(int d);
const char* GetDirNm(int dir);
#endif
