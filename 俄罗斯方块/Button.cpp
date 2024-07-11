#include "Button.h"
using namespace std;
void Button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(32, 0, L"Á¥Êé");
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	fillroundrect(this->x, this->y, this->x + this->width, this->y + this->height, 35, 35);
	RECT rect = {x, y, x + width, y + height};
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Button::drawbutton2()
{
	setfillcolor(this->color);
	settextstyle(25, 0, L"Î¢ÈíÑÅºÚ");
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	fillroundrect(this->x, this->y, this->x + this->width, this->y + this->height, 15, 15);
	RECT rect = {x, y, x + width, y + height};
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
bool Button::mouseinbutton(MOUSEMSG m)
{
	if (this->x <= m.x && m.x <= this->x + this->width && this->y <= m.y && m.y <= this->height + this->y)
	{
		this->color = LIGHTCYAN;
		return true;
	}
	this->color = LIGHTGRAY;
	return false;
}

bool Button::clickbutton(MOUSEMSG m)
{
	if (mouseinbutton(m) && m.uMsg == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}