#pragma once
#ifndef GAME_H
#define GAME_H
#include <easyx.h>
#include <ctime>


#define MAP_WIDTH 10   // ��ͼ���,10������
#define MAP_HEIGHT 20  // ��ͼ�߶�,20������
#define BLOCK_WIDTH 20 // ������,20����
// ��Ϸ��
class Game
{
public:
	void drawMap() const;						// ���Ƶ�ͼ
	void drawPrompt() const;					// ������ʾ����
	bool checkLine(const unsigned& line) const; // �ж�����
	void clearLine();							// �������

	// ��������
public:
	// ���õ�ͼ
	void setMap(const int& x, const int& y, const bool& value)
	{
		map[x][y] = value;
	}

	// ��ȡ��ͼ
	const bool& getMap(const int& x, const int& y) const
	{
		return map[x][y];
	}
private:
	bool map[MAP_WIDTH][MAP_HEIGHT] = { 0 }; // ��ͼ����
	unsigned score = 0;					   // ��Ϸ����

};
#endif
