#include "main.h"
using namespace std;
void Msg::Reset()
{
	sprintf(text, "");
	attrn = 0;
}

void Msg::print()
{
	attron(attr[attrn]);
	printw(text);
	attroff(attr[attrn]);
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
	for (int ny = p1.y; ny <= p2.y; ny++)
	{
		move(ny, 0);
		clrtoeol();
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
	move(p1.y, p1.x);
	for (int i = 0; i < mxmsg; i++)
	{
		move(cy() + 1, p1.x);
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
	if (np1.x < 0)
	{
		np1.x = 0;
	}
	else if (np1.x >= scr_w)
	{
		np1.x = scr_w - 1;
	}
	if (np1.y < 0)
	{
		np1.y = 0;
	}
	else if (np1.y >= scr_h)
	{
		np1.y = scr_h - 1;
	}
	if (np2.x < 0)
	{
		np2.x = 0;
	}
	else if (np2.x >= scr_w)
	{
		np2.x = scr_w - 1;
	}
	if (np2.y < 0)
	{
		np2.y = 0;
	}
	else if (np2.y >= scr_h)
	{
		np2.y = scr_h - 1;
	}
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
	msg[t].attrn = 0;
}

void MsgBox::print(int attrn, const char *msgs, ...);
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
	msg[t].attrn = attrn;
}

void MsgBox::add(const char *msgs, ...)
{
	if (!ena)
	{
		return;
	}
	char tmpt[100];
	va_list arg;
	va_start(arg, msgs);
	vsprintf(tmpt, msgs, arg);
	va_end(arg);
	strcat(msg[cmsg - 1].text, tmpt);
}

void MsgBox::SetAttr(int n)
{
	msg[cmsg - 1].attrn = n;
}