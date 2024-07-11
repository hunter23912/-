#include "Block.h"

bool Block::blockData[7][4][4] = {0};

Block::Block(Game &game, const int &x, const int &y) : game(game), x(x), y(y)
{
	type = rand() % 7; // 随机方块类型
	direction = 1;

	// 设置方块填充颜色
	switch (type)
	{
	case 0:
		color = LIGHTBLUE;
		break;

	case 1:
		color = GREEN;
		break;

	case 2:
		color = LIGHTGREEN;
		break;

	case 3:
		color = YELLOW;
		break;

	case 4:
		color = RED;
		break;

	case 5:
		color = CYAN;
		break;

	case 6:
		color = MAGENTA;
	}

	// 复制方块数据
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[i][j] = blockData[type][i][j];
		}
	}
}

bool Block::move(const unsigned &direction)
{
	switch (direction)
	{
	case 0: // 向下加速
		y++;
		if (checkCollision())
		{
			y--;
			return true;
		}
		break;

	case 1: // 向左移动
		x--;
		if (checkCollision())
		{
			x++;
		}
		break;

	case 2: // 向右移动
		x++;
		if (checkCollision())
		{
			x--;
		}
		break;
	}
	return false;
}

void Block::draw() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[i][j])
			{
				// 绘制方块，Y坐标为负时不绘制
				if (j + y >= 0)
				{
					setfillcolor(color);
					int left = 20 + BLOCK_WIDTH * (x + i), top = 20 + BLOCK_WIDTH * (j + y);
					fillrectangle(left, top, left + BLOCK_WIDTH, top + BLOCK_WIDTH);
				}
			}
		}
	}
}

void Block::clear() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[i][j])
			{
				// 清除方块
				int left = 20 + BLOCK_WIDTH * (x + i), top = 20 + BLOCK_WIDTH * (j + y);
				clearrectangle(left, top, left + BLOCK_WIDTH, top + BLOCK_WIDTH);
			}
		}
	}
}

void Block::addMap() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[i][j])
			{
				// 添加方块
				game.setMap(x + i, y + j, block[i][j]);
			}
		}
	}
}

void Block::rotate()
{
	// 田字方块不旋转
	if (type != 4)
	{
		// 只旋转左上角3*3区域
		bool temp;
		if (direction == 0) // 顺时针旋转
		{
			// 四个角旋转
			temp = block[0][0];
			block[0][0] = block[0][2];
			block[0][2] = block[2][2];
			block[2][2] = block[2][0];
			block[2][0] = temp;

			// 棱旋转
			temp = block[1][0];
			block[1][0] = block[0][1];
			block[0][1] = block[1][2];
			block[1][2] = block[2][1];
			block[2][1] = temp;
		}
		else // 逆时针旋转
		{
			// 角旋转
			temp = block[0][0];
			block[0][0] = block[2][0];
			block[2][0] = block[2][2];
			block[2][2] = block[0][2];
			block[0][2] = temp;

			// 十字中心旋转
			temp = block[1][0];
			block[1][0] = block[2][1];
			block[2][1] = block[1][2];
			block[1][2] = block[0][1];
			block[0][1] = temp;
		}

		// 处理其它方块的特殊情况
		switch (type)
		{
			// 长条方块
		case 0:
			if (block[1][3]) // 将长条形方块的最后一个方块修改到旋转后的位置
			{
				block[1][3] = 0;
				block[3][1] = 1;
			}
			else
			{
				block[1][3] = 1;
				block[3][1] = 0;
			}
			break;

			// Z字方块正和Z字方块反
		case 5:
		case 6:
			// 没有发生碰撞才执行此操作
			if (!checkCollision())
			{
				direction = !direction;
			}
		}

		// 碰撞检查，如果发生碰撞则往相反方向旋转一次
		if (checkCollision())
		{
			// 相反方向旋转
			if (direction == 1) // 顺时针旋转
			{
				// 角旋转
				temp = block[0][0];
				block[0][0] = block[0][2];
				block[0][2] = block[2][2];
				block[2][2] = block[2][0];
				block[2][0] = temp;

				// 十字中心旋转
				temp = block[1][0];
				block[1][0] = block[0][1];
				block[0][1] = block[1][2];
				block[1][2] = block[2][1];
				block[2][1] = temp;
			}
			else // 逆时针旋转
			{
				// 角旋转
				temp = block[0][0];
				block[0][0] = block[2][0];
				block[2][0] = block[2][2];
				block[2][2] = block[0][2];
				block[0][2] = temp;

				// 十字中心旋转
				temp = block[1][0];
				block[1][0] = block[2][1];
				block[2][1] = block[1][2];
				block[1][2] = block[0][1];
				block[0][1] = temp;
			}
			if (type == 0)
			{
				if (block[1][3])
				{
					block[1][3] = 0;
					block[3][1] = 1;
				}
				else
				{
					block[1][3] = 1;
					block[3][1] = 0;
				}
			}
		}
	}
}

bool Block::checkCollision() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// 判断方块是否与地图发生碰撞，顶部不判断
			if ((game.getMap(x + i, y + j) || 20 + BLOCK_WIDTH * (x + i) < 20 || 20 + BLOCK_WIDTH * (x + i) + BLOCK_WIDTH > 220 || 20 + BLOCK_WIDTH * (j + y) + BLOCK_WIDTH > 420) && block[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

void Block::generateBlockData()
{
	// 长条方块
	blockData[0][1][0] = blockData[0][1][1] = blockData[0][1][2] = blockData[0][1][3] = true;
	// 七字方块正
	blockData[1][0][0] = blockData[1][1][0] = blockData[1][1][1] = blockData[1][1][2] = true;
	// 七字方块反
	blockData[2][2][0] = blockData[2][1][0] = blockData[2][1][1] = blockData[2][1][2] = true;
	// 凸字方块
	blockData[3][1][0] = blockData[3][0][1] = blockData[3][1][1] = blockData[3][2][1] = true;
	// 田字方块
	blockData[4][0][0] = blockData[4][1][0] = blockData[4][0][1] = blockData[4][1][1] = true;
	// Z字方块正
	blockData[5][0][0] = blockData[5][1][0] = blockData[5][1][1] = blockData[5][2][1] = true;
	// Z字方块反
	blockData[6][2][0] = blockData[6][1][0] = blockData[6][1][1] = blockData[6][0][1] = true;
}

void Block::setPos(const int &x, const int &y)
{
	this->x = x;
	this->y = y;
}

void Block::randType()
{
	type = rand() % 7; // 随机方块类型，生成一个0~6的数字
	direction = 1;

	// 设置方块填充颜色
	switch (type)
	{
	case 0: // 长条形
		color = LIGHTBLUE;
		break;

	case 1: // 七字方块正
		color = GREEN;
		break;

	case 2: // 七字方块反
		color = LIGHTGREEN;
		break;

	case 3: // 凸字方块
		color = YELLOW;
		break;

	case 4: // 田字方块
		color = RED;
		break;

	case 5: // Z字方块正
		color = CYAN;
		break;

	case 6: // Z字方块反
		color = MAGENTA;
	}

	// 复制方块数据
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[i][j] = blockData[type][i][j];
		}
	}
}

void Block::operator=(const Block &block)
{
	x = block.x;
	y = block.y;
	type = block.type;
	direction = block.direction;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->block[i][j] = block.block[i][j];
		}
	}
	color = block.color;
}