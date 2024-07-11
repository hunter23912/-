#ifndef BUTTON_H
#define BUTTON_H
#include <graphics.h>
#include <string>
using namespace std;
class Button
{
public:
	Button(int x, int y, int width, int height, COLORREF color, const wstring &text = L"°´Å¥")
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->color = color;
		this->text = text;
	}
	void drawbutton();
	void drawbutton2();
	bool mouseinbutton(MOUSEMSG m);
	bool clickbutton(MOUSEMSG m);
	COLORREF &getColor()
	{
		return color;
	}

protected:
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	wstring text;
};
#endif // !BUTTON_H
