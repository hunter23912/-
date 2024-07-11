#pragma once
#ifndef GAME_H
#define GAME_H
#include <easyx.h>
#include <ctime>


#define MAP_WIDTH 10   // 地图宽度,10个方块
#define MAP_HEIGHT 20  // 地图高度,20个方块
#define BLOCK_WIDTH 20 // 方块宽度,20像素
// 游戏类
class Game
{
public:
	void drawMap() const;						// 绘制地图
	void drawPrompt() const;					// 绘制提示界面
	bool checkLine(const unsigned& line) const; // 判断满行
	void clearLine();							// 清除满行

	// 内联函数
public:
	// 设置地图
	void setMap(const int& x, const int& y, const bool& value)
	{
		map[x][y] = value;
	}

	// 获取地图
	const bool& getMap(const int& x, const int& y) const
	{
		return map[x][y];
	}
private:
	bool map[MAP_WIDTH][MAP_HEIGHT] = { 0 }; // 地图数组
	unsigned score = 0;					   // 游戏分数

};
#endif
