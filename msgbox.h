#ifndef _MSGBOX_H_
#define _MSGBOX_H_
#include "def.h"
class Msg
{
  public:
	char text[100];
	int attrn;
	void Reset();
	void print();
};

class MsgBox
{
  public:
	pos p1;
	pos p2;
	int cmsg;
	int ena;
	Msg msg[mxmsg];
	void Reset();
	void Wipe();
	void Init(pos np1, pos np2);
	void DrawBodr();
	void Show();
	void Clear();
	void SetPos(pos np1, pos np2);
	void Scroll(int n);
	void print(const char *msgs, ...);
	void print(int nattrn, const char *msgs, ...);
	void add(const char *msgs, ...);
	void SetAttr(int n);
};
#endif
