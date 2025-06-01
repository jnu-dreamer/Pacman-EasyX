#include "ghosts.h"
#include <cstdlib>
#include "config.h"

Ghost::Ghost(int startX, int startY, COLORREF ghostColor)
    : x(startX), y(startY), dir(DIRECTIONS[rand() % 4]), speed(1), color(ghostColor) {}

void Ghost::reset(int startX, int startY) {
    x = startX;
    y = startY;
    dir = DIRECTIONS[rand() % 4];
}

void Ghost::update() {
    if (rand() % 10 == 0) {
        std::vector<std::pair<int, int>> validDirs;
        for (auto d : DIRECTIONS) {
            int nx = x + d.first, ny = y + d.second;
            if (nx >= 0 && nx < COLS && ny >= 0 && ny < ROWS && mp[ny][nx] != 1)
                validDirs.push_back(d);
        }
        if (!validDirs.empty())
            dir = validDirs[rand() % validDirs.size()];
    }

    int nx = x + dir.first, ny = y + dir.second;
    if (nx >= 0 && nx < COLS && ny >= 0 && ny < ROWS && mp[ny][nx] != 1) {
        x = nx;
        y = ny;
    }
}

void Ghost::draw() {
    int block_size = 25;
    setfillcolor(color);
    fillcircle(x * block_size + block_size / 2, y * block_size + block_size / 2, block_size / 2 - 2);
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }
