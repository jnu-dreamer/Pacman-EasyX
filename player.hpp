#pragma once
#include "mover.hpp"
#include "map.hpp"

using namespace std;

class Player : public mover
{
private:
	bool isalive = true;
	int lives = 4;
	int score = 0;
	pair<int, int> nxtdir = { 0, 0 }; // 用于存储新的方向
	bool invincible = false;      // 是否无敌
	int invincibleTimer = 0;      // 剩余无敌帧数（假设每帧update一次）
	const int INVINCIBLE_DURATION = 300; // 无敌帧
public:
	Player() {} 
	Player(int x, int y, int speed = 0, IMAGE* img = nullptr) : mover(x, y, speed, img) {} 

	void reset()
	{
		nxtdir = { 0, 0 }; // 重置方向
		x = 13 * block_size; y = 14 * block_size; // 重置位置
		dir = RIGHT; // 初始方向向右
	}

	void update() override // 虚函数实现，更新玩家状态
	{
		if (x <= 1 && y / block_size == 12 && dir == LEFT)
		{
			x = block_size * (COLS - 1); // 右侧出口
			mp[y / block_size][COLS - 1] = 2; // 将豆子变为空地
			score += 10;        // 增加分数
		}
		else if (x >= block_size * (COLS - 1) && y / block_size == 12 && dir == RIGHT)
		{
			x = block_size * 0; // 左侧出口
		}

        // 移动处理由主循环中的按键处理负责
        // 只负责根据当前方向移动
        int newx = x + dir.first*speed;
		int newy = y + dir.second * speed;

		bool iscenter = (x % block_size == 0 && y % block_size == 0); // 检查是否在格子中心

		// 如果在格子中心，检查是否可以转向 nxtDir
		if (iscenter && canMoveTo(x + nxtdir.first * speed, y + nxtdir.second * speed))
		{
			//std::cout << 10;
			dir = nxtdir;
		}

		newx = x + dir.first * speed;
		newy = y + dir.second * speed;
        // 检查是否可以移动
		if (canMoveTo(newx, newy))
		{
			//std::cout << newy / block_size;
			x = newx;
			y = newy;

			// 吃豆子
			if (mp[newy / block_size][newx / block_size] == 0)
			{
				mp[newy / block_size][newx / block_size] = 2; // 将豆子变为空地
				score += 10;        // 增加分数
			}

			if (mp[newy / block_size][newx / block_size] == 3)
			{
				mp[newy / block_size][newx / block_size] = 2;
				score += 30;

				// 进入无敌状态
				invincible = true;
				invincibleTimer = INVINCIBLE_DURATION;
			}
		}

		// 无敌计时递减
		if (invincible)
		{
			invincibleTimer--;
			if (invincibleTimer <= 0)
			{
				invincible = false;
				invincibleTimer = 0;
			}
		}
	}

	bool collision(int ghostX, int ghostY) // 碰撞检测
	{
		if (invincible) return false; // 无敌时不被吃a
		const int COLLISION_DISTANCE = block_size / 2; 
		int dx = x - ghostX;
		int dy = y - ghostY;
		return dx * dx + dy * dy <= COLLISION_DISTANCE * COLLISION_DISTANCE; // 鬼怪与玩家欧氏距离小于等于半个格子即视为碰撞（被吃）
	}

	void die() // 玩家死亡一次
	{
		lives--;
		isalive = lives > 0;
		if (isalive) reset();
	}

	void draw(int idx)
	{
		int idy = 0;
		if (dir == RIGHT) idy = 0;
		if (dir == LEFT) idy = 1;
		if (dir == UP) idy = 2;
		if (dir == DOWN) idy = 3;
		if (invincibleTimer != 0 && invincibleTimer <= 100 && invincibleTimer % 10 < 6)
		{
			return;
		}
		drawImg(x, y, 24, 24, img, idx * 24, idy * 24);
	}

	void setDirection(const pair<int, int>& newDir) { nxtdir = newDir; }
	bool isALive() const { return isalive; }
	void setLives(int lives) { this->lives = lives; }
	int getScore() const { return score; }
	int getLives() const { return lives; }
	void setScore(int s){ this->score = s; }
};