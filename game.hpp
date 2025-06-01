#pragma once
#include "player.hpp"
#include "ghost.hpp"
#include <iostream>
#include <vector>
void renderGame();
void Input();
void controlFPS(clock_t start);
void updateGame();
void StartScreen();
void GameOver();
void GameWin();
void resetGame();           // ÷ÿ÷√”Œœ∑

extern Player player;
extern vector<Ghost> ghosts;
extern int frameTime;
extern int frame;
extern int speed;
extern int gameState;
