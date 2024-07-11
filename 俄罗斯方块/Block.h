#ifndef BLOCK_H
#define BLOCK_H

#include "Game.h"

// 方块类
class Block
{
public:
	Block(Game &game, const int &x = (MAP_WIDTH - 4) / 2, const int &y = 0); // 初始化函数
	bool move(const unsigned &direction = 0);								 // 移动函数，0下移一格，1左移一格，2右移一格，当下移检测到碰撞时返回true
	void draw() const;														 // 绘制函数，绘制指定形状的方块
	void clear() const;														 // 清除函数，清除指定形状的方块
	void addMap() const;													 // 添加方块到地图
	void rotate();															 // 旋转方块
	bool checkCollision() const;											 // 碰撞检查
	static void generateBlockData();										 // 初始化方块数据，制造方块
	void setPos(const int &x = (MAP_WIDTH - 4) / 2, const int &y = 0);		 // 设置方块坐标
	void randType();														 // 随机方块类型
	void operator=(const Block &block);										 // 为Block赋值

private:
	int x;							// 方块X坐标
	int y;							// 方块Y坐标
	unsigned char type;				// 方块类型
	bool direction;					// 旋转方向，false代表顺时针，true代表逆时针
	bool block[4][4];				// 方块数组，true表示有方块，false表示没方块颜色
	COLORREF color;					// 方块填充颜色
	static bool blockData[7][4][4]; // 方块数据，对象共享的资源
	Game &game;						// Game引用对象
};
#endif