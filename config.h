#pragma once
#include <utility>
#include <easyx.h>
#include <cmath>
#include "tool.hpp"
#include <vector>
#include <iostream>
const int block_size = 24;
const int ROWS = 29;
const int COLS = 27;
const int FPS = 17;
const int GHOST_COUNT = 4;
const double pi = acos(-1);

const std::pair<int, int> UP = { 0, -1 };
const std::pair<int, int> DOWN = { 0, 1 };
const std::pair<int, int> LEFT = { -1, 0 };
const std::pair<int, int> RIGHT = { 1, 0 };
const std::pair<int, int> DIRECTIONS[4] = { UP, DOWN, LEFT, RIGHT };

const int WIN = 1, LOSE = 2, PLAYING = 3, READY = 4;
const int running = 1;
const int ghost_count = 4;

extern IMAGE heart;
extern int mp[ROWS][COLS]; // 2 表示空地，1 表示墙，0 表示豆子
extern int mpcopy[ROWS][COLS]; // 2 表示空地，1 表示墙，0 表示豆子
extern int vis[ROWS][COLS];
extern IMAGE pacman, ghost[5];