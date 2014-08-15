#include "main.h"
using namespace std;
void Msg::Reset()
{
	sprintf(text, "");
	attr = 0;
}

void Msg::print()
{
	attron(attr);
	printw(text);
	attroff(attr);
}

void MsgBox::Reset()
{
	Clear();
	p1.Reset();
	p2.Reset();
	cmsg = 0;
	ena = 0;
}

void MsgBox::Wipe()
{
	move(p1.y, p1.x);
	int y = 0, x = 0;
	while (1)
	{
		printw(" ");
		getyx(stdscr, y, x);
		if (x == p2.x && y == p2.y)
		{
			return;
		}
	}
}

void MsgBox::Init(pos np1, pos np2)
{
	SetPos(np1, np2);
	ena = 1;
}

void MsgBox::DrawBodr()
{
	move(p1.y, p1.x);
	printw("+");
	for (int i = 1; i < p2.x - p1.x; i++)
	{
		printw("=");
	}
	move(p2.y, p1.x);
	for (int i = 0; i < p2.x - p1.x; i++)
	{
		printw("=");
	}
}

void MsgBox::Show()
{
	int tx, ty;
	getyx(stdscr, ty, tx);
	Wipe();
	DrawBodr();
	for (int i = 0; i < mxmsg; i++)
	{
		move(p1.y + i + 1, p1.x);
		msg[i].print();
	}
	move(ty, tx);
}

void MsgBox::Clear()
{
	for (int i = 0; i < mxmsg; i++)
	{
		msg[i].Reset();
	}
}

void MsgBox::SetPos(pos np1, pos np2)
{
	p1 = np1;
	p2 = np2;
}

void MsgBox::Scroll(int n)
{
	for (int i = 0; i < mxmsg - n; i++)
	{
		msg[i] = msg[i + n];
		msg[i + n].Reset();
	}
}

void MsgBox::print(const char *msgs, ...)
{
	if (!ena)
	{
		return;
	}
	int t = mxmsg - 1;
	if (cmsg == mxmsg)
	{
		Scroll(1);
	}
	else
	{
		t = cmsg++;
	}
	va_list arg;
	va_start(arg, msgs);
	vsprintf(msg[t].text, msgs, arg);
	va_end(arg);
	msg[t].attr = 0;
}