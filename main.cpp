#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>
#include <utility>
#include <chrono>
#include <easyx.h>
#include <graphics.h>
#include "ghost.hpp"
#include "player.hpp"
#include "map.hpp"
#include "game.hpp"
using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	IMAGE pacman, ghost[5];

	// 加载图片
	loadimage(&pacman, L"pic/pacman.png");
	loadimage(&ghost[4], L"pic/dead.png");
	loadimage(&ghost[0], L"pic/blue.png");
	loadimage(&ghost[1], L"pic/orange.png");
	loadimage(&ghost[2], L"pic/pink.png");
	loadimage(&ghost[3], L"pic/red.png");
	loadimage(&heart, L"pic/heart.png");
	
	// 创建窗口
	initgraph((COLS) * block_size, (ROWS + 1) * block_size, 0);

	// 初始化玩家与鬼怪
	player.setImg(&pacman);
	player.setX(13 * block_size);
	player .setY(14 * block_size);
	player.setSpeed(4);
	for (int i = 0; i < ghost_count + 1; i++) ghosts.push_back(Ghost((12 + i)*block_size, 12*block_size, 1, &ghost[i]));

	int startTime = 0;

	while (true)
	{
		startTime = clock();

		Input(); // 处理输入
		updateGame(); // 更新游戏状态
		renderGame(); // 渲染游戏画面

		controlFPS(startTime); // 控制帧率
		frame++;
	}


	system("pause");

	return 0;
}