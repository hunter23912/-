#include "head.h"

int main()
{
	int gap = 500;
	int a = 5;
BEGIN:
	SetWindowText(initgraph(350, 440), L"俄罗斯方块");
	IMAGE img_bg;
	loadimage(&img_bg, L"1.jpg");
	setbkcolor(WHITE);
	cleardevice();
	putimage(-512, -512, &img_bg);
	Button* level1 = new Button(125, 120, 100, 40, LIGHTGRAY, L"简单");
	Button* level2 = new Button(125, 170, 100, 40, LIGHTGRAY, L"普通");
	Button* level3 = new Button(125, 220, 100, 40, LIGHTGRAY, L"困难");
	Button* rule = new Button(125, 270, 100, 40, LIGHTGRAY, L"规则");
	Sleep(50);
	while (1)
	{
		level1->drawbutton();
		level2->drawbutton();
		level3->drawbutton();
		rule->drawbutton();
		FlushBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		if (level1->clickbutton(m))
		{
			closegraph();
			gap = 350;
			delete level1;
			delete level2;
			delete level3;
			break;
		}
		if (level2->clickbutton(m))
		{
			closegraph();
			gap = 250;
			delete level1;
			delete level2;
			delete level3;
			break;
		}
		if (level3->clickbutton(m))
		{
			closegraph();
			gap = 150;
			delete level1;
			delete level2;
			delete level3;
			break;
		}
		if (rule->clickbutton(m))
		{
			delete level1;
			delete level2;
			delete level3;
			closegraph();
			SetWindowText(initgraph(694, 300), L"rule");
			IMAGE img_rule;
			loadimage(&img_rule, L"2.png");
			setbkcolor(WHITE);
			cleardevice();
			putimage(0, 0, &img_rule);
			Button* fanhui = new Button(600, 260, 50, 30, LIGHTGRAY, L"返回");
			while (1)
			{
				fanhui->drawbutton2();
				FlushBatchDraw();
				MOUSEMSG m = GetMouseMsg();
				if (fanhui->clickbutton(m))
					goto BEGIN;
			}
		}
	}
	SetWindowText(initgraph(350, 440), L"俄罗斯方块");
	setbkcolor(WHITE);
	cleardevice();

	setlinecolor(BLACK);

	// 生成游戏界面和数据
	srand(time(NULL));
	Block::generateBlockData();

	Game game;
	game.drawMap();
	game.drawPrompt();

	Block b(game);//定义了一个Block类型的变量b，并将game作为参数传递给b
	Block nextBlock(game, 11, 2); // 下一方块
	clock_t start = 0;			  // 时钟开始时间
	clock_t end;				  // 时钟结束时间

	ExMessage msg;

	nextBlock.draw();//绘制右边的下一个方块

	// 游戏循环
	BeginBatchDraw();//开始批量绘图，先将绘图操作缓存起来，绘图结束后统一显示出来
	while (true)
	{
		b.clear();//清除方块
		clearrectangle(20, 20, 220, 420);//清空主屏幕
		game.drawMap();

		// 按键按下
		while (peekmessage(&msg, EX_KEY) && msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
				// 上键旋转
			case 'W':
			case VK_UP:
				b.rotate();
				break;

				// 下键加速下落
			case 'S':
			case VK_DOWN:
				if (b.move())//move函数没填传入参数，默认为0
				{
					// 重新设置方块
					b.addMap();
					b = nextBlock;
					b.setPos();
					nextBlock.clear();
					nextBlock.setPos(11, 2);
					nextBlock.randType();
					nextBlock.draw();

					// 如果方块刚刚生成却发生了碰撞，说明游戏结束
					if (b.checkCollision())
					{
						MessageBox(GetHWnd(), L"游戏结束！", L"提示", MB_ICONWARNING);
						goto exit;
					}
				}
				break;

				// 左键移动
			case 'A':
			case VK_LEFT:
				b.move(1);
				break;

				// 右键移动
			case 'D':
			case VK_RIGHT:
				b.move(2);
				break;

				// Esc键退出程序
			case VK_ESCAPE:
				goto exit;
				break;
			}
		}

		// 判断每过了gap毫秒方块下移一格
		end = clock();
		if (end - start >= gap)
		{
			if (b.move())//条件成立表示方块撞墙
			{
				// 重新设置方块
				b.addMap();
				b = nextBlock;
				b.setPos();
				nextBlock.clear();
				nextBlock.setPos(11, 2);
				nextBlock.randType();
				nextBlock.draw();

				// 如果方块刚刚生成却发生了碰撞，说明游戏结束
				if (b.checkCollision())
				{
					MessageBox(GetHWnd(), L"游戏结束！", L"提示", MB_ICONWARNING);
					goto exit;
				}
			}
			start = clock();
		}
		b.draw();
		game.clearLine();
		FlushBatchDraw(); // 刷新缓冲区，将此前批量绘制的图像显示在屏幕上
		Sleep(10);		  // 每10毫秒接受一次按键
	}

exit:
	EndBatchDraw();

	closegraph();
	return 0;
}
