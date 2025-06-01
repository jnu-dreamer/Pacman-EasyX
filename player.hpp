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
	pair<int, int> nxtdir = { 0, 0 }; // ���ڴ洢�µķ���
	bool invincible = false;      // �Ƿ��޵�
	int invincibleTimer = 0;      // ʣ���޵�֡��������ÿ֡updateһ�Σ�
	const int INVINCIBLE_DURATION = 300; // �޵�֡
public:
	Player() {} 
	Player(int x, int y, int speed = 0, IMAGE* img = nullptr) : mover(x, y, speed, img) {} 

	void reset()
	{
		nxtdir = { 0, 0 }; // ���÷���
		x = 13 * block_size; y = 14 * block_size; // ����λ��
		dir = RIGHT; // ��ʼ��������
	}

	void update() override // �麯��ʵ�֣��������״̬
	{
		if (x <= 1 && y / block_size == 12 && dir == LEFT)
		{
			x = block_size * (COLS - 1); // �Ҳ����
			mp[y / block_size][COLS - 1] = 2; // �����ӱ�Ϊ�յ�
			score += 10;        // ���ӷ���
		}
		else if (x >= block_size * (COLS - 1) && y / block_size == 12 && dir == RIGHT)
		{
			x = block_size * 0; // ������
		}

        // �ƶ���������ѭ���еİ���������
        // ֻ������ݵ�ǰ�����ƶ�
        int newx = x + dir.first*speed;
		int newy = y + dir.second * speed;

		bool iscenter = (x % block_size == 0 && y % block_size == 0); // ����Ƿ��ڸ�������

		// ����ڸ������ģ�����Ƿ����ת�� nxtDir
		if (iscenter && canMoveTo(x + nxtdir.first * speed, y + nxtdir.second * speed))
		{
			//std::cout << 10;
			dir = nxtdir;
		}

		newx = x + dir.first * speed;
		newy = y + dir.second * speed;
        // ����Ƿ�����ƶ�
		if (canMoveTo(newx, newy))
		{
			//std::cout << newy / block_size;
			x = newx;
			y = newy;

			// �Զ���
			if (mp[newy / block_size][newx / block_size] == 0)
			{
				mp[newy / block_size][newx / block_size] = 2; // �����ӱ�Ϊ�յ�
				score += 10;        // ���ӷ���
			}

			if (mp[newy / block_size][newx / block_size] == 3)
			{
				mp[newy / block_size][newx / block_size] = 2;
				score += 30;

				// �����޵�״̬
				invincible = true;
				invincibleTimer = INVINCIBLE_DURATION;
			}
		}

		// �޵м�ʱ�ݼ�
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

	bool collision(int ghostX, int ghostY) // ��ײ���
	{
		if (invincible) return false; // �޵�ʱ������a
		const int COLLISION_DISTANCE = block_size / 2; 
		int dx = x - ghostX;
		int dy = y - ghostY;
		return dx * dx + dy * dy <= COLLISION_DISTANCE * COLLISION_DISTANCE; // ��������ŷ�Ͼ���С�ڵ��ڰ�����Ӽ���Ϊ��ײ�����ԣ�
	}

	void die() // �������һ��
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