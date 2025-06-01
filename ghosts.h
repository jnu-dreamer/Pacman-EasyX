#pragma once
#include <utility>
#include <vector>
#include <graphics.h>

#include "config.h"
extern int mp[ROWS][COLS]; // 引用地图数组

class Ghost {
private:
    int x, y;
    std::pair<int, int> dir;
    int speed;
    COLORREF color;

public:
    Ghost(int startX, int startY, COLORREF ghostColor);
    void reset(int startX, int startY);
    void update();
    void draw();
    int getX() const;
    int getY() const;
};
