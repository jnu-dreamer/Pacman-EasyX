#pragma once
#include "mover.hpp"
#include "map.hpp"
#include <queue>
#include <vector>   
#include <utility>
using namespace std;

class Ghost : public mover
{
public:
    Ghost(int x, int y, int speed = 1, IMAGE* image = nullptr) : mover(x, y, speed, image) {}

    void reset(int setx, int sety)
    {
        x = setx;
        y = sety;
        dir = DIRECTIONS[rand() % 4];
    }

    // Ghost���ڲ������bfsNextDirection����
    // ����ֵ��pair<int,int>����ʾ�������磺
    // ��(0,-1), ��(0,1), ��(-1,0), ��(1,0)
    // ����Ҳ���·�������� (0,0)
    pair<int, int> bfs(int playerX, int playerY) {
        // ����������ת��Ϊ��ͼ��������
        int startRow = y / block_size;
        int startCol = x / block_size;
        int targetRow = playerY / block_size;
        int targetCol = playerX / block_size;

        // ����������յ㣬ֱ�ӷ��ز���
        if (startRow == targetRow && startCol == targetCol) {
            return { 0, 0 };
        }

        // �ĸ������ҡ����¡���
        static const vector<pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        // ���ڼ�¼�Ƿ���ʹ�
        bool visited[ROWS][COLS] = { false };

        // ����·�����ݣ���¼ÿ�����Ӵ��ĸ�������
        pair<int, int> prev[ROWS][COLS];
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                prev[i][j] = { -1, -1 };

        queue<pair<int, int>> q;
        q.push({ startRow, startCol });
        visited[startRow][startCol] = true;

        bool found = false;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == targetRow && c == targetCol) {
                found = true;
                break;
            }

            for (auto& d : directions) {
                int nr = r + d.second;  // ע��pair��{dx, dy}������y������d.second
                int nc = c + d.first;   // ����x������d.first

                // Խ������Ƿ��ͨ��
                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS
                    && !visited[nr][nc] && mp[nr][nc] != 1)  // 1Ϊǽ��������
                {
                    visited[nr][nc] = true;
                    prev[nr][nc] = { r, c };
                    q.push({ nr, nc });
                }
            }
        }

        if (!found) {
            return { 0, 0 }; // û�ҵ�·��������ԭ����
        }

        // ���յ���ݵ���㣬�ҵ���һ����λ��
        int curR = targetRow, curC = targetCol;
        pair<int, int> last = { curR, curC };
        while (prev[curR][curC] != make_pair(startRow, startCol)) {
            auto p = prev[curR][curC];
            curR = p.first;
            curC = p.second;
        }
        // curR, curC �ǹ�ֵ�ǰλ���ڽӸ��ӣ�����һ��Ҫ�ߵĸ���

        // ת���ɷ�������
        int dx = curC - startCol;
        int dy = curR - startRow;

        return { dx, dy };
    }

    void update() override
    {
        // ��һ����������ı䷽��
        if (rand() % 10 == 0 && x % block_size == 0 && y % block_size == 0) {
            // ��ȡ���з���
            vector<pair<int, int>> validDirs;
            for (const auto& d : DIRECTIONS) {
                int newX = x + d.first * speed;
                int newY = y + d.second * speed;
                if (canMoveTo(newX, newY)) {
                    validDirs.push_back(d);
                }
            }

            // ����п��з������ѡ��һ��
            if (!validDirs.empty())
                dir = validDirs[rand() % validDirs.size()];


        }

        // �ƶ���
        int newX = x + dir.first * speed;
        int newY = y + dir.second * speed;

        // ����Ƿ�����ƶ�
        if (canMoveTo(newX, newY)) {
            x = newX;
            y = newY;
        }
        else
        {
            // ����ǽ�����ѡ��һ���·���
            vector<pair<int, int>> validDirs;
            for (const auto& d : DIRECTIONS) {
                if (d != dir) { // ����ԭ����
                    newX = x + d.first * speed;
                    newY = y + d.second * speed;
                    if (canMoveTo(newX, newY)) {
                        validDirs.push_back(d);
                    }
                }
            }

            // ����п��з������ѡ��һ��
            if (!validDirs.empty()) {
                dir = validDirs[rand() % validDirs.size()];
            }
        }
    }
    // �����������
    void update(int playerX, int playerY) 
    {
        // ���ڸ�������ʱѰ·
        if (x % block_size == 0 && y % block_size == 0) {
            auto nextDir = bfs(playerX, playerY);
            // �����·�����·���
            if (nextDir != make_pair(0, 0)) {
                dir = nextDir;
            }
        }
        int newX = x + dir.first * speed;
        int newY = y + dir.second * speed;
        if (canMoveTo(newX, newY)) {
            x = newX;
            y = newY;
        }
    }
    void antibfs(int playerX, int playerY) {
        // ֻ�ڸ�������ʱ�ı䷽��
        if (x % block_size != 0 || y % block_size != 0) {
            int newX = x + dir.first * speed;
            int newY = y + dir.second * speed;
            if (canMoveTo(newX, newY)) {
                x = newX;
                y = newY;
            }
            return;
        }

        int curRow = y / block_size;
        int curCol = x / block_size;
        int playerRow = playerY / block_size;
        int playerCol = playerX / block_size;

        // 1. BFS����ҳ���������ÿ�����ӵ���ҵ���̾���
        int dist[ROWS][COLS];
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                dist[i][j] = -1;

        queue<pair<int, int>> q;
        q.push({ playerRow, playerCol });
        dist[playerRow][playerCol] = 0;

        static const vector<pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (auto& d : directions) {
                int nr = r + d.second;
                int nc = c + d.first;
                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && mp[nr][nc] != 1 && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({ nr, nc });
                }
            }
        }

        // 2. ѡ����������Զ�ķ���
        int maxDist = dist[curRow][curCol];
        pair<int, int> bestDir = dir;
        vector<pair<int, int>> validDirs;
        for (const auto& d : directions) {
            int newRow = curRow + d.second;
            int newCol = curCol + d.first;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && mp[newRow][newCol] != 1) {
                validDirs.push_back(d);
                if (dist[newRow][newCol] != -1 && dist[newRow][newCol] > maxDist)
                {
                    maxDist = dist[newRow][newCol];
                    bestDir = d;
                }
            }
        }

        // ���û�и�Զ�ķ������ѡһ�����з��򣬱��⿨ס
        if (bestDir == dir && !validDirs.empty()) {
            bestDir = validDirs[rand() % validDirs.size()];
        }

        dir = bestDir;
        int newX = x + dir.first * speed;
        int newY = y + dir.second * speed;
        if (canMoveTo(newX, newY)) {
            x = newX;
            y = newY;
        }
    }
};
