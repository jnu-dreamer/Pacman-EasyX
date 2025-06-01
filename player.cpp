#include "player.h"
#include "map.h"
#include "config.h"
#include <graphics.h>
#include <cmath>

const double pi = acos(-1);

Player::Player(int x, int y) : x(x), y(y), dir(RIGHT), speed(2), score(0), lives(3), isalive(true) {}

void Player::reset() {
    x = 15; y = 14;
    dir = RIGHT;
}

void Player::update() {
    int newx = x + dir.first * speed;
    int newy = y + dir.second * speed;
    if (newx >= 0 && newx < COLS && newy >= 0 && newy < ROWS && mp[newy][newx] != 1) {
        x = newx; y = newy;
        if (mp[newy][newx] == 0) {
            mp[newy][newx] = 2;
            score += 10;
        }
    }
}

void Player::setDirection(const std::pair<int, int>& newDir) {
    int checkX = x + newDir.first;
    int checkY = y + newDir.second;
    if (checkX >= 0 && checkX < COLS && checkY >= 0 && checkY < ROWS && mp[checkY][checkX] != 1) {
        dir = newDir;
    }
}

void Player::draw() {
    int screenX = x * block_size;
    int screenY = y * block_size;
    double startAngle = 30 * pi / 180;
    double endAngle = 330 * pi / 180;
    setfillcolor(YELLOW);
    solidpie(screenX, screenY, screenX + block_size, screenY + block_size, startAngle, endAngle);
}

bool Player::collision(int ghostX, int ghostY) {
    return x == ghostX && y == ghostY;
}

void Player::die() {
    lives--;
    isalive = lives > 0;
    if (isalive) reset();
}

bool Player::isAlive() const { return isalive; }
int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getScore() const { return score; }
int Player::getLives() const { return lives; }
