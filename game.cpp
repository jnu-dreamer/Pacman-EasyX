#include "game.hpp"
#include "map.hpp"
#include <graphics.h>
#include <conio.h>
#include <ctime>

int frameTime = 0;
int frame = 0;
int speed = 150;
int gameState = READY; 
int difficulty = 1; // 1=简单, 2=普通, 3=困难
IMAGE heart;
Player player;
vector<Ghost> ghosts;

void renderGame() 
{
    BeginBatchDraw();
    cleardevice();

    if (gameState == READY) 
    {
        StartScreen();
        EndBatchDraw();
        return;
    }

    if (gameState == LOSE) 
    {
        GameOver();
        EndBatchDraw();
        return;
    }

    if (gameState == WIN)
    {
        GameWin();
        EndBatchDraw();
        return;
    }

    drawMap();

    int t = clock() / speed;
    int pacman_index = t % 3;
    int ghost_index = t % 2;

    player.draw(pacman_index);
    for (int i = 0; i < 4; i++) 
        ghosts[i].draw(ghost_index);    

    // 绘制剩余生命
    int lives = player.getLives();
    for (int i = 0; i < lives; i++) 
    {
        int x = i * block_size;
        int y = (ROWS) * block_size;
        drawImg(x + 13*block_size, y, 24, 24, &heart, 0, 0);
	}
	// 绘制剩余豆子
    int remaindots = countDots();
    TCHAR dotsText[20];
    _stprintf_s(dotsText, _T("Remaining Dots: %d"), remaindots);
    settextstyle(20, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));
    outtextxy(10, (ROWS + 1) * block_size - 20, dotsText);
    // 绘制分数
    TCHAR scoreText[20];
    _stprintf_s(scoreText, _T("Score: %d"), player.getScore());
    outtextxy((COLS - 5) * block_size, (ROWS + 1) * block_size - 20 , scoreText);

    EndBatchDraw();
}

void Input() {
    while (_kbhit()) 
    {
        int key = _getch();
        if (key == 224) key = _getch(); // 方向键
        if (isalpha(key)) key = toupper(key);

        // 处理开始界面难度选择
        if (gameState == READY) 
        {
            if (key == 72) { // 上
                difficulty = (difficulty == 1) ? 3 : difficulty - 1;
            }
            else if (key == 80) { // 下
                difficulty = (difficulty == 3) ? 1 : difficulty + 1;
            }
            else if (key == 13) { // 回车
                // 根据难度设置参数
                switch (difficulty) 
                {
                case 1:
                    player.setLives(5);
                    ghosts[0].setSpeed(3);
                    ghosts[1].setSpeed(1);
                    ghosts[2].setSpeed(1);
                    ghosts[3].setSpeed(2);
                    break;
                case 2:
                    player.setLives(3);
                    ghosts[0].setSpeed(3);
                    ghosts[1].setSpeed(3);
                    ghosts[2].setSpeed(1);
                    ghosts[3].setSpeed(2);
                    break;
                case 3:
                    player.setLives(1);
                    ghosts[0].setSpeed(4);
                    ghosts[1].setSpeed(3);
                    ghosts[2].setSpeed(3);
                    ghosts[3].setSpeed(3);
                    break;
                }
                gameState = PLAYING; 
            }
            return; // 只处理READY状态的输入
        }

        // 游戏中操作
        if (gameState == PLAYING) 
        {
            switch (key) {
            case 72: case 'W': player.setDirection(UP); break;
            case 80: case 'S': player.setDirection(DOWN); break;
            case 75: case 'A': player.setDirection(LEFT); break;
            case 77: case 'D': player.setDirection(RIGHT); break;
            }
        }
    }
}

void updateGame()
{
    if (gameState == PLAYING)
    {
        player.update();
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < ghost_count; j ++)
                {
                    if (i == j) continue;
                    vis[ghosts[j].getY() / block_size][ghosts[j].getX() / block_size] = 1;
                }
                
                if (i == 0 && frame % 100 > 10) ghosts[i].update();
                else if (i == 1 && frame % 100 > 30) ghosts[i].update();
                else ghosts[i].update(player.getX(), player.getY());

                for (int j = 0; j < ghost_count; j++)
                    vis[ghosts[j].getY() / block_size][ghosts[j].getX() / block_size] = 0;

                if (player.collision(ghosts[i].getX(), ghosts[i].getY())) 
                {
                    player.die();
                    if (!player.isALive()) 
                        gameState = LOSE;
                    break;
                }
            }
        }
    }
    if (countDots() == 0) 
	{
		gameState = WIN; // 如果豆子吃完了，游戏胜利
	}
}

void controlFPS(clock_t start)
{
    frameTime = clock() - start;
    int delay = FPS - frameTime;
    if (delay > 0)
        Sleep(delay);
}

void StartScreen() 
{
    int win_w = COLS * block_size;
    int win_h = (ROWS + 1) * block_size;

    // 绘制渐变背景（黑到深蓝）
    for (int y = 0; y < win_h; ++y) {
        int blue = 30 + (int)(150.0 * y / win_h); 
        setlinecolor(RGB(10, 10, blue));
        line(0, y, win_w, y);
    }

    // 标题
    const TCHAR* title = _T("Pacman");
    setbkmode(TRANSPARENT);

    settextstyle(64, 0, _T("Times New Roman"));
    settextcolor(RGB(50, 50, 50)); // 阴影
    outtextxy((win_w - textwidth(title)) / 2 + 4, win_h / 6 + 4, title);

    settextcolor(RGB(255, 215, 0)); // 金黄色
    outtextxy((win_w - textwidth(title)) / 2, win_h / 6, title);

    // 难度选择标题
    settextstyle(28, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));
    const TCHAR* sel = _T("Select Difficulty:");
    int sel_w = textwidth(sel);
    int sel_y = win_h / 3;
    outtextxy((win_w - sel_w) / 2, sel_y, sel);

    // 分割线
    setlinecolor(RGB(120, 120, 120));
    line(win_w / 4, sel_y + 36, win_w * 3 / 4, sel_y + 36);

    // 难度选项
    int opt_y = sel_y + 60;
    int opt_gap = 52;
    const TCHAR* options[] = {
        _T("1. Easy Version"),
        _T("2. Medium Version"),
        _T("3. Hard Version")
    };

    settextstyle(28, 0, _T("Times New Roman"));
    for (int i = 0; i < 3; ++i) {
        int opt_w = textwidth(options[i]);
        int opt_x = (win_w - opt_w) / 2;
        int opt_cur_y = opt_y + i * opt_gap;

        if (difficulty == i + 1) {
            setfillcolor(RGB(255, 240, 180));
            setlinecolor(RGB(255, 140, 0));
            fillroundrect(opt_x - 16, opt_cur_y - 6, opt_x + opt_w + 16, opt_cur_y + 36, 22, 22);
            settextcolor(RGB(255, 60, 60));
        }
        else {
            settextcolor(RGB(255, 255, 255));
        }
        outtextxy(opt_x, opt_cur_y, options[i]);
    }

    // 底部提示语
    settextstyle(22, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));
    const TCHAR* tip1 = _T("Use ↑↓ to select");
    const TCHAR* tip2 = _T("Press Enter to start");

    int tip1_w = textwidth(tip1);
    int tip2_w = textwidth(tip2);
    outtextxy((win_w - tip1_w) / 2, win_h - 90, tip1);
    outtextxy((win_w - tip2_w) / 2, win_h - 60, tip2);
}

void GameOver() 
{
    int win_w = COLS * block_size;
    int win_h = (ROWS + 1) * block_size;

    // 渐变背景（黑到暗红色）
    for (int y = 0; y < win_h; ++y) {
        int red = 20 + (int)(100.0 * y / win_h); 
        setlinecolor(RGB(red, 0, 0));
        line(0, y, win_w, y);
    }

    // “游戏结束” 标题
    const TCHAR* title = _T("Game Over");
    setbkmode(TRANSPARENT);
    settextstyle(64, 0, _T("Times New Roman"));

    settextcolor(RGB(50, 0, 0));  // 阴影
    outtextxy((win_w - textwidth(title)) / 2 + 4, win_h / 4 + 4, title);

    settextcolor(RGB(255, 0, 0));  // 正文
    outtextxy((win_w - textwidth(title)) / 2, win_h / 4, title);

    // 提示文字
    const TCHAR* tip = _T("Press any key to return");
    TCHAR scoreText[20];
    _stprintf_s(scoreText, _T("Score: %d"), player.getScore());
    settextstyle(28, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));
    outtextxy((win_w - textwidth(tip)) / 2, win_h / 2, tip);
    outtextxy((win_w - textwidth(tip)) / 2 + 70, win_h / 2 -60, scoreText);
    settextstyle(20, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));

    // 非阻塞检测按键
    static bool keyPressed = false;
    if (!keyPressed && _kbhit()) 
    {
        int ch = _getch(); // 吃掉按键
        keyPressed = true;
        gameState = READY;
        resetGame(); 
    }

    if (gameState != LOSE) 
    {
        keyPressed = false;
    }
}

void GameWin()
{
    int win_w = COLS * block_size;
    int win_h = (ROWS + 1) * block_size;

    // 渐变背景（黑到亮蓝色）
    for (int y = 0; y < win_h; ++y) {
        int blue = 80 + (int)(120.0 * y / win_h);
        setlinecolor(RGB(0, 80, blue));
        line(0, y, win_w, y);
    }

    // “YOU WIN!” 标题
    const TCHAR* title = _T("YOU WIN!");
    setbkmode(TRANSPARENT);
    settextstyle(64, 0, _T("Times New Roman"));

    settextcolor(RGB(0, 0, 80));  // 阴影
    outtextxy((win_w - textwidth(title)) / 2 + 4, win_h / 4 + 4, title);

    settextcolor(RGB(0, 255, 255));  // 正文
    outtextxy((win_w - textwidth(title)) / 2, win_h / 4, title);

    // 提示文字
    const TCHAR* tip = _T("Press any key to return");
    TCHAR scoreText[20];
    _stprintf_s(scoreText, _T("Score: %d"), player.getScore());
    settextstyle(28, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));
    outtextxy((win_w - textwidth(tip)) / 2, win_h / 2, tip);
    outtextxy((win_w - textwidth(tip)) / 2 + 70, win_h / 2 - 60, scoreText);
    settextstyle(20, 0, _T("Times New Roman"));
    settextcolor(RGB(255, 255, 255));

    // 非阻塞检测按键
    static bool keyPressed = false;
    if (!keyPressed && _kbhit())
    {
        int ch = _getch(); // 吃掉按键
        keyPressed = true;
        gameState = READY;
        resetGame();
    }

    if (gameState != WIN)
    {
        keyPressed = false;
    }
}

void resetGame()           // 重置游戏
{
    player.setX(13 * block_size);
    player.setY(14 * block_size);
    player.setSpeed(4);
    for (int i = 0; i < ghost_count; i++) ghosts[i].setX((12 + i) * block_size), ghosts[i].setY(12 * block_size);
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            vis[i][j] = 0, mp[i][j] = mpcopy[i][j];
    player.setScore(0);
}
