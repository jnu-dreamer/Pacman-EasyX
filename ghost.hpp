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

    // Ghost类内部，添加bfsNextDirection函数
    // 返回值是pair<int,int>，表示方向，例如：
    // 上(0,-1), 下(0,1), 左(-1,0), 右(1,0)
    // 如果找不到路径，返回 (0,0)
    pair<int, int> bfs(int playerX, int playerY) {
        // 将像素坐标转换为地图格子坐标
        int startRow = y / block_size;
        int startCol = x / block_size;
        int targetRow = playerY / block_size;
        int targetCol = playerX / block_size;

        // 如果起点就是终点，直接返回不动
        if (startRow == targetRow && startCol == targetCol) {
            return { 0, 0 };
        }

        // 四个方向：右、左、下、上
        static const vector<pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        // 用于记录是否访问过
        bool visited[ROWS][COLS] = { false };

        // 用于路径回溯，记录每个格子从哪个格子来
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
                int nr = r + d.second;  // 注意pair是{dx, dy}，行是y方向，用d.second
                int nc = c + d.first;   // 列是x方向，用d.first

                // 越界检测和是否可通过
                if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS
                    && !visited[nr][nc] && mp[nr][nc] != 1)  // 1为墙，不能走
                {
                    visited[nr][nc] = true;
                    prev[nr][nc] = { r, c };
                    q.push({ nr, nc });
                }
            }
        }

        if (!found) {
            return { 0, 0 }; // 没找到路径，保持原方向
        }

        // 从终点回溯到起点，找到下一步的位置
        int curR = targetRow, curC = targetCol;
        pair<int, int> last = { curR, curC };
        while (prev[curR][curC] != make_pair(startRow, startCol)) {
            auto p = prev[curR][curC];
            curR = p.first;
            curC = p.second;
        }
        // curR, curC 是鬼怪当前位置邻接格子，是下一步要走的格子

        // 转换成方向向量
        int dx = curC - startCol;
        int dy = curR - startRow;

        return { dx, dy };
    }

    void update() override
    {
        // 有一定概率随机改变方向
        if (rand() % 10 == 0 && x % block_size == 0 && y % block_size == 0) {
            // 获取可行方向
            vector<pair<int, int>> validDirs;
            for (const auto& d : DIRECTIONS) {
                int newX = x + d.first * speed;
                int newY = y + d.second * speed;
                if (canMoveTo(newX, newY)) {
                    validDirs.push_back(d);
                }
            }

            // 如果有可行方向，随机选择一个
            if (!validDirs.empty())
                dir = validDirs[rand() % validDirs.size()];


        }

        // 移动鬼
        int newX = x + dir.first * speed;
        int newY = y + dir.second * speed;

        // 检查是否可以移动
        if (canMoveTo(newX, newY)) {
            x = newX;
            y = newY;
        }
        else
        {
            // 遇到墙，随机选择一个新方向
            vector<pair<int, int>> validDirs;
            for (const auto& d : DIRECTIONS) {
                if (d != dir) { // 避免原方向
                    newX = x + d.first * speed;
                    newY = y + d.second * speed;
                    if (canMoveTo(newX, newY)) {
                        validDirs.push_back(d);
                    }
                }
            }

            // 如果有可行方向，随机选择一个
            if (!validDirs.empty()) {
                dir = validDirs[rand() % validDirs.size()];
            }
        }
    }
    // 传入玩家坐标
    void update(int playerX, int playerY) 
    {
        // 仅在格子中心时寻路
        if (x % block_size == 0 && y % block_size == 0) {
            auto nextDir = bfs(playerX, playerY);
            // 如果有路，更新方向
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
        // 只在格子中心时改变方向
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

        // 1. BFS从玩家出发，计算每个格子到玩家的最短距离
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

        // 2. 选择距离玩家最远的方向
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

        // 如果没有更远的方向，随机选一个可行方向，避免卡住
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
