#include "Game.h"

void Game::drawMap() const
{
	// 绘制边框
	roundrect(10, 10, 340, 430, 10, 10); // 绘制一个圆角矩形
	rectangle(20, 20, 220, 420);		 // 绘制界面左边的直角矩形

	// 绘制已落下的方块
	setfillcolor(LIGHTCYAN);
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (map[i][j])
			{
				int left = 20 + 20 * i, top = 20 + 20 * j;
				fillrectangle(left, top, left + 20, top + 20);
			}
		}
	}
}

void Game::drawPrompt() const
{
	// 设置字体
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	wcscpy_s(f.lfFaceName, L"微软雅黑");
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);

	// 绘制下一方块提示
	outtextxy(235, 20, L"下一方块");
	rectangle(240, 60, 320, 140);

	// 绘制分数和时间
	f.lfHeight = 25;
	settextstyle(&f);

	wchar_t str[10];
	wsprintf(str, L"分数：%u", score);
	outtextxy(230, 150, str);

	// wsprintf(str, L"时间：%u秒", gameTime / 1000);
	// outtextxy(230, 175, str);

	// 绘制俄罗斯方块
	f.lfHeight = 30;
	settextstyle(&f);
	settextcolor(RED);
	outtextxy(250, 250, L"俄罗斯");
	outtextxy(260, 290, L"方块");

	// 绘制作者
	f.lfHeight = 22;
	settextstyle(&f);
	outtextxy(234, 380, L"作者：汪江豪");
}

bool Game::checkLine(const unsigned &line) const
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (map[i][line] == 0)
		{
			return false;
		}
	}
	return true;
}

void Game::clearLine()
{
	int line = -1;
	// 判断哪一行满行
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		if (checkLine(j))
		{
			line = j;
			break;
		}
	}

	if (line != -1)
	{
		// 将上一行移至满行
		for (int j = line; j > 0; j--)
		{
			for (int i = 0; i < MAP_WIDTH; i++)
			{
				map[i][j] = map[i][j - 1];
			}
		}
		score += 10; // 将游戏分数加 10
	}
	drawPrompt();
}