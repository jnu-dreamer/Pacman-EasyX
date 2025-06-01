//#include <iostream>
//#include <cmath>
//#include <easyx.h>
//#include <graphics.h>
//#include <conio.h>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <string>
//#include <utility>
//#include <windows.h> // 添加Windows API支持
//using namespace std;
//
//const double pi = acos(-1);
//// 方向常量
//const pair<int, int> UP = { 0, -1 };
//const pair<int, int> DOWN = { 0, 1 };
//const pair<int, int> LEFT = { -1, 0 };
//const pair<int, int> RIGHT = { 1, 0 };
//const pair<int, int> DIRECTIONS[4] = { UP, DOWN, LEFT, RIGHT };
//
//// 游戏参数
//const int block_size = 30;   // 每个格子大小为 25 像素
//const int ROWS = 29;
//const int COLS = 27;
//const int GHOST_COUNT = 4;  // 鬼的数量
//const int FPS = 20;         // 游戏刷新率
//
//// 游戏状态
//enum GameState {
//    START_SCREEN,
//    PLAYING,
//    GAME_OVER,
//    WIN
//};
//
//// 全局变量
//int mp[ROWS][COLS] = // 2 表示空地，1 表示墙，0 表示豆子
//{
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
//    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1},
//    {1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
//    {1,1,1,1,1,1,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,1,1,1,1,1,1},
//    {2,2,2,2,2,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,2,2,2,2,2},
//    {2,2,2,2,2,1,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1,2,2,2,2,2},
//    {2,2,2,2,2,1,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,2,2},
//    {1,1,1,1,1,1,0,1,0,1,2,2,2,2,2,2,2,1,0,1,0,1,1,1,1,1,1},
//    {0,0,0,0,0,0,0,1,0,1,2,2,2,2,2,2,2,1,0,1,0,0,0,0,0,0,0},
//    {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1},
//    {2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2},
//    {2,2,2,2,2,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,2,2,2,2,2},
//    {2,2,2,2,2,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,2,2,2,2,2},
//    {2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2},
//    {2,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,2},
//    {2,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,2},
//    {2,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,2},
//    {2,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,2},
//    {2,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,2},
//    {2,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,2},
//    {2,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,2},
//    {2,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,2},
//    {2,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,2},
//    {2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
//    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
//};
//
//// 统计豆子数量
//int Dotscnt() {
//    int count = 0;
//    for (int i = 0; i < ROWS; i++) 
//        for (int j = 0; j < COLS; j++) 
//            if (mp[i][j] == 0) count++;
//        
//    return count;
//}
//    
//// 玩家类
//class Player 
//{
//private:
//    bool isalive = true;
//    int x, y;
//    pair<int, int> dir;
//    int speed;
//    int score;
//    int lives;
//
//public:
//    Player(int x = 13, int y = 23) : x(x), y(y), dir(RIGHT), speed(1), score(0), lives(3) {}
//
//    void reset() 
//    {
//        x = 15;
//        y = 14;
//        dir = RIGHT;
//    }
//
//    void update() 
//    {
//        // 移动处理由主循环中的按键处理负责
//        // 只负责根据当前方向移动
//        int newx = x + dir.first;
//        int newy = y + dir.second;
//
//        // 检查是否可以移动
//        if (newx >= 0 && newx < COLS && newy >= 0 && newy < ROWS && mp[newy][newx] != 1) {
//            x = newx;
//            y = newy;
//
//            // 吃豆子
//            if (mp[newy][newx] == 0) {
//                mp[newy][newx] = 2; // 将豆子变为空地
//                score += 10;        // 增加分数
//            }
//        }
//    }
//
//    void setDirection(const pair<int, int>& newDir) {
//        // 检查新方向是否有效（不能直接撞墙）
//        int checkX = x + newDir.first;
//        int checkY = y + newDir.second;
//
//        if (checkX >= 0 && checkX < COLS && checkY >= 0 && checkY < ROWS && mp[checkY][checkX] != 1) {
//            dir = newDir;
//        }
//    }
//
//    void draw() {
//        int screenX = x * block_size;
//        int screenY = y * block_size;
//        int radius = block_size / 2 - 2;
//
//        // 根据方向设置张嘴角度
//        double startAngle, endAngle;
//        if (dir == RIGHT) {
//            startAngle = 30 * 1.0 / 180 * pi;
//            endAngle = 330 * 1.0 / 180 * pi;
//        }
//        else if (dir == LEFT) {
//            startAngle = 210 * 1.0 / 180 * pi;
//            endAngle = 150 * 1.0 / 180 * pi;
//        }
//        else if (dir == UP) {
//            startAngle = 120 * 1.0 / 180 * pi;
//            endAngle = 60 * 1.0 / 180 * pi;
//        }
//        else { // DOWN
//            startAngle = 300 * 1.0 / 180 * pi;
//            endAngle = 240 * 1.0 / 180 * pi ;
//        }
//        setfillcolor(YELLOW);
//        solidpie(screenX + 4, screenY + 4, screenX + block_size - 4, screenY + block_size - 4, startAngle, endAngle);
//        setlinecolor(BLACK);
//        pie(screenX, screenY, screenX + block_size, screenY + block_size, startAngle, endAngle);
//    }
//
    //bool collision(int ghostX, int ghostY) {
    //    return x == ghostX && y == ghostY;
    //}
//
//    void die() 
//    {
//        lives--;
//        isalive = lives > 0;
//        if (isalive) reset();
//    }
//
//    bool isAlive() const { return isalive; }
//    int getX() const { return x; }
//    int getY() const { return y; }
//    int getScore() const { return score; }
//    int getLives() const { return lives; }
//};
//
//// 鬼类
//class Ghost {
//private:
//    int x, y;
//    pair<int, int> dir;
//    int speed;
//    COLORREF color;
//
//public:
//    Ghost(int startX, int startY, COLORREF ghostColor)
//        : x(startX), y(startY), dir(RIGHT), speed(1), color(ghostColor) {}
//
//    void reset(int startX, int startY) {
//        x = startX;
//        y = startY;
//        // 随机初始方向
//        dir = DIRECTIONS[rand() % 4];
//    }
//
//    void update() {
//        // 有一定概率随机改变方向
//        if (rand() % 10 == 0) {
//            // 获取可行方向
//            vector<pair<int, int>> validDirs;
//            for (const auto& d : DIRECTIONS) {
//                int newX = x + d.first;
//                int newY = y + d.second;
//                if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS && mp[newY][newX] != 1) {
//                    validDirs.push_back(d);
//                }
//            }
//
//            // 如果有可行方向，随机选择一个
//            if (!validDirs.empty()) {
//                dir = validDirs[rand() % validDirs.size()];
//            }
//        }
//
//        // 移动鬼
//        int newX = x + dir.first;
//        int newY = y + dir.second;
//
//        // 检查是否可以移动
//        if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS && mp[newY][newX] != 1) {
//            x = newX;
//            y = newY;
//        }
//        else {
//            // 遇到墙，随机选择一个新方向
//            vector<pair<int, int>> validDirs;
//            for (const auto& d : DIRECTIONS) {
//                if (d != dir) { // 避免原方向
//                    newX = x + d.first;
//                    newY = y + d.second;
//                    if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS && mp[newY][newX] != 1) {
//                        validDirs.push_back(d);
//                    }
//                }
//            }
//
//            // 如果有可行方向，随机选择一个
//            if (!validDirs.empty()) {
//                dir = validDirs[rand() % validDirs.size()];
//            }
//        }
//    }
//
//    void draw() {
//        int screenX = x * block_size;
//        int screenY = y * block_size;
//
//        // 画鬼身体
//        setfillcolor(color);
//        solidroundrect(screenX + 5, screenY + 5, screenX + block_size - 5, screenY + block_size - 5, 5, 5);
//
//        // 画眼睛
//        setfillcolor(WHITE);
//        solidcircle(screenX + block_size / 3, screenY + block_size / 3, 3);
//        solidcircle(screenX + block_size * 2 / 3, screenY + block_size / 3, 3);
//
//        // 画眼珠
//        setfillcolor(BLACK);
//        solidcircle(screenX + block_size / 3 + dir.first * 2, screenY + block_size / 3 + dir.second * 2, 1);
//        solidcircle(screenX + block_size * 2 / 3 + dir.first * 2, screenY + block_size / 3 + dir.second * 2, 1);
//    }
//
//    int getX() const { return x; }
//    int getY() const { return y; }
//};
//
//// 绘制地图
//    void drawMap() {
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                int x = j * block_size;
//                int y = i * block_size;
//
//                switch (mp[i][j]) {
//                case 2: // 空地
//                    setfillcolor(BLACK);
//                    solidrectangle(x, y, x + block_size, y + block_size);
//                    break;
//                case 1: // 墙
//                    setfillcolor(BLUE);
//                    solidrectangle(x, y, x + block_size, y + block_size);
//                    setlinecolor(LIGHTBLUE);
//                    rectangle(x, y, x + block_size, y + block_size);
//                    break;
//                case 0: // 豆子
//                    setfillcolor(BLACK);
//                    solidrectangle(x, y, x + block_size, y + block_size);
//                    setfillcolor(WHITE);
//                    fillcircle(x + block_size / 2, y + block_size / 2, 3);
//                    break;
//                }
//            }
//        }
//    }
//
//// 绘制开始界面
//void drawStartScreen(int frame) {
//    cleardevice();
//    setbkcolor(BLACK);
//    cleardevice();
//
//    settextcolor(YELLOW);
//    settextstyle(40, 0, L"Consolas");
//    outtextxy(100, 100, L"欢迎来到吃豆人游戏");
//
//    // 画一个简单的张嘴吃豆人动画，左右移动
//    int x = 100 + (frame % 100);
//    int y = 200;
//    int r = 25;
//    int angle = 20 + 10 * sin(frame * 0.2);
//
//    double startAngle = 0;
//    if ((frame / 50) % 2 == 0) startAngle = angle; // 向右张嘴
//    else startAngle = 180 + angle;                 // 向左张嘴
//
//    setfillcolor(YELLOW);
//    solidpie(x - r, y - r, x + r, y + r, startAngle, startAngle + 360 - 2 * angle);
//
//    // 绘制鬼
//    int ghostY = 200;
//    COLORREF ghostColors[] = { RED, MAGENTA, CYAN, GREEN };
//    for (int i = 0; i < GHOST_COUNT; i++) {
//        int ghostX = x + 100 + i * 50;
//        setfillcolor(ghostColors[i]);
//        solidroundrect(ghostX - 20, ghostY - 20, ghostX + 20, ghostY + 20, 5, 5);
//        setfillcolor(WHITE);
//        solidcircle(ghostX - 7, ghostY - 7, 5);
//        solidcircle(ghostX + 7, ghostY - 7, 5);
//        setfillcolor(BLACK);
//        solidcircle(ghostX - 7, ghostY - 7, 2);
//        solidcircle(ghostX + 7, ghostY - 7, 2);
//    }
//
//    settextcolor(WHITE);
//    settextstyle(20, 0, L"Consolas");
//    outtextxy(100, 300, L"按空格键开始游戏");
//    outtextxy(100, 330, L"使用WASD键控制吃豆人");
//}
//
//// 绘制游戏结束界面
//void drawGameOver(int score) {
//    cleardevice();
//    settextcolor(RED);
//    settextstyle(50, 0, L"Consolas");
//    outtextxy(150, 200, L"游戏结束");
//
//    settextcolor(WHITE);
//    settextstyle(30, 0, L"Consolas");
//    wstring scoreText = L"最终得分: " + to_wstring(score);
//    outtextxy(150, 270, scoreText.c_str());
//
//    settextstyle(20, 0, L"Consolas");
//    outtextxy(150, 320, L"按空格键重新开始");
//    outtextxy(150, 350, L"按ESC键退出游戏");
//}
//
//// 绘制胜利界面
//void drawWin(int score) {
//    cleardevice();
//    settextcolor(YELLOW);
//    settextstyle(50, 0, L"Consolas");
//    outtextxy(150, 200, L"恭喜你赢了!");
//
//    settextcolor(WHITE);
//    settextstyle(30, 0, L"Consolas");
//    wstring scoreText = L"最终得分: " + to_wstring(score);
//    outtextxy(150, 270, scoreText.c_str());
//
//    settextstyle(20, 0, L"Consolas");
//    outtextxy(150, 320, L"按空格键重新开始");
//    outtextxy(150, 350, L"按ESC键退出游戏");
//}
//
//// 绘制状态栏
//void drawStatusBar(int score, int lives, int dotsLeft) {
//    settextcolor(WHITE);
//    settextstyle(18, 0, L"Consolas");
//
//    wstring scoreText = L"分数: " + to_wstring(score);
//    outtextxy(10, ROWS * block_size + 5, scoreText.c_str());
//
//    wstring livesText = L"生命: " + to_wstring(lives);
//    outtextxy(200, ROWS * block_size + 5, livesText.c_str());
//
//    wstring dotsText = L"剩余豆子: " + to_wstring(dotsLeft);
//    outtextxy(350, ROWS * block_size + 5, dotsText.c_str());
//}
//
//// 重置游戏
//void resetGame(Player& player, vector<Ghost>& ghosts, int originalMap[ROWS][COLS]) {
//    // 恢复原始地图
//    for (int i = 0; i < ROWS; i++) {
//        for (int j = 0; j < COLS; j++) {
//            mp[i][j] = originalMap[i][j];
//        }
//    }
//
//    // 重置玩家
//    player = Player();
//
//    // 重置鬼
//    for (int i = 0; i < ghosts.size(); i++) {
//        ghosts[i].reset(11 + i, 14);
//    }
//}
//
//int main() {
//    // 初始化随机数种子
//    srand(static_cast<unsigned int>(time(nullptr)));
//
//    // 初始化图形界面
//    initgraph(COLS * block_size, ROWS * block_size + 30,0);
//    setbkcolor(BLACK);
//
//    cleardevice();
//
//    // 备份原始地图，用于游戏重置
//    int originalMap[ROWS][COLS];
//    for (int i = 0; i < ROWS; i++) {
//        for (int j = 0; j < COLS; j++) {
//            originalMap[i][j] = mp[i][j];
//        }
//    }
//
//    // 创建玩家
//    Player player;
//
//    // 创建鬼
//    vector<Ghost> ghosts;
//    COLORREF ghostColors[] = { RED, MAGENTA, CYAN, GREEN };
//    for (int i = 0; i < GHOST_COUNT; i++) {
//        ghosts.push_back(Ghost(11 + i, 12, ghostColors[i]));
//    }
//
//    // 游戏状态
//    GameState gameState = START_SCREEN;
//
//    // 初始豆子数量
//    int totalDots = Dotscnt();
//    int frame = 0;
//    bool running = true;
//
//    // 设置控制台标题
//    SetConsoleTitle(L"吃豆人游戏");
//
//    // 显示调试信息，便于排错
//    HWND hwnd = GetConsoleWindow();
//    if (hwnd) {
//        ShowWindow(hwnd, SW_SHOW);
//    }
//
//    while (running) {
//        // 清屏
//        cleardevice();
//        BeginBatchDraw();
//        // 处理按键输入（改进按键检测和处理方式）
//        while (_kbhit()) {
//            int key = _getch();
//
//            // 处理方向键的两个字节输入
//            if (key == 224) {  // 方向键的前导字节
//                key = _getch(); // 获取方向键的第二个字节
//                switch (key) {
//                case 72: // 上箭头
//                    if (gameState == PLAYING) {
//                        player.setDirection(UP);
//                    }
//                    break;
//                case 80: // 下箭头
//                    if (gameState == PLAYING) {
//                        player.setDirection(DOWN);
//                    }
//                    break;
//                case 75: // 左箭头
//                    if (gameState == PLAYING) {
//                        player.setDirection(LEFT);
//                    }
//                    break;
//                case 77: // 右箭头
//                    if (gameState == PLAYING) {
//                        player.setDirection(RIGHT);
//                    }
//                    break;
//                }
//                continue;
//            }
//            if (isalpha(key)) key = toupper(key);
//            // 处理标准按键
//            switch (key) {
//            case 27: // ESC键退出
//                running = false;
//                break;
//
//            case 32: // 空格键
//                if (gameState == START_SCREEN) {
//                    gameState = PLAYING;
//                }
//                else if (gameState == GAME_OVER || gameState == WIN) {
//                    // 重置游戏
//                    resetGame(player, ghosts, originalMap);
//                    totalDots = Dotscnt();
//                    gameState = PLAYING;
//                }
//                break;
//
//            case 'W': 
//                if (gameState == PLAYING) {
//                    player.setDirection(UP);
//                }
//                break;
//
//            case 'S': 
//                if (gameState == PLAYING) {
//                    player.setDirection(DOWN);
//                }
//                break;
//
//            case 'A':
//                if (gameState == PLAYING) {
//                    player.setDirection(LEFT);
//                }
//                break;
//
//            case 'D':
//                if (gameState == PLAYING) {
//                    player.setDirection(RIGHT);
//                }
//                break;
//            }
//        }
//
//        // 变量声明（放在switch语句之前）
//        int dotsLeft = 0;
//
//        // 根据游戏状态更新和绘制
//        switch (gameState) {
//        case START_SCREEN:
//            drawStartScreen(frame);
//            break;
//
        //case PLAYING:
        //    // 更新玩家
        //    player.update();
//
//            // 更新鬼
//            if (frame % 2 == 0) 
//            for (auto& ghost : ghosts) {
//                ghost.update();
//
//                // 检查碰撞
//                if (player.collision(ghost.getX(), ghost.getY())) {
//                    player.die();
//                    if (!player.isAlive()) {
//                        gameState = GAME_OVER;
//                    }
//                    break;
//                }
//            }
//
//            // 检查胜利条件
//            dotsLeft = Dotscnt();
//            if (dotsLeft == 0) {
//                gameState = WIN;
//            }
//
//            // 绘制地图和角色
//            drawMap();
//            player.draw();
//            for (auto& ghost : ghosts) {
//                ghost.draw();
//            }
//	
//            // 绘制状态栏
//            drawStatusBar(player.getScore(), player.getLives(), dotsLeft);
//            break;
//
//        case GAME_OVER:
//            drawGameOver(player.getScore());
//            break;
//
//        case WIN:
//            drawWin(player.getScore());
//            break;
//        }
//
//        // 控制帧率
//        Sleep(1000 / FPS);
//        frame++;
//        EndBatchDraw();
//    }
//
//    // 关闭图形界面
//    closegraph();
//    return 0;
//}