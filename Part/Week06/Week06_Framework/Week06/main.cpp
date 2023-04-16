/**
 *  File: main.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/15 00:41:55
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/04/16 23:14:36
 *  Description: 基本輸入方向移動功能，w s a d 移動腳色上下左右，
 *               空白改變腳色站立之地板字元，到T上可以增加經驗，
 *               ESC是離開畫面。同時更新圖版上的資訊。
 */

#include "main.h"
#include "Hero.h"

Hero gHero(2, 2);

// Creature Class
class Creature
{
private:
    Position sPos;    // Creature position
    char sIcon = 'C'; // Creature icon
    int power;

public:
    // Default constructor
    Creature(void)
    {
        this->sPos.x = 1;
        this->sPos.y = 1;
        this->sIcon = 'C';
        this->power = 5;
    };

    // Set position
    void setPos(Position pos) { this->sPos = pos; }
    void setPos(int x, int y)
    {
        this->sPos.x = x;
        this->sPos.y = y;
    }

    // Set icon
    void setIcon(char &icon) { this->sIcon = icon; }

    // Get position
    Position getPos(void) { return this->sPos; }

    // Get Icon
    char getIcon(void) { return this->sIcon; }

public:
    void update(Hero &hero)
    {
        Position hPos = hero.getPos();

        Position dir;
        if ( canSee(this->sPos, hPos, dir) )
        {
            std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
            this->sIcon = '!';
        }
        else
        {
            std::cout << "Creature didn't find the Hero\n";
            this->sIcon = 'C';
        }

        if ( hPos.x == sPos.x && hPos.y == sPos.y )
        {
            hero.damage(power);
        }
    }
};

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 10;
const int GHEIGHT = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char gBoard[GHEIGHT][GWIDTH];

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
    EW = 0,
    ES = 1,
    EA = 2,
    ED = 3,
    ESPACE = 4,
    EESC = 5,
    EJUMP,
    INVALID,
};

Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard();
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

Trigger gTrigger(5, 5, 10);
int globalJumpX, globalJumpY;

int main(int argc, char **argv)
{
    srand(time(NULL));

    // 用來管理鍵盤輸入狀態的陣列
    bool gKeyState[ValidInput::INVALID];
    for ( int i = 0; i < 6; i++ )
    {
        gKeyState[i] = false;
    }

    // Setup a clear dungeon
    setupBoard();

    gCreature.setPos(5, 6);

    // Draw the bord and information
    draw();
    drawInfo();

    // Variable for game loop
    clock_t startT, endT;
    startT = clock();
    endT = clock();

    // Run the game loop
    while ( !gKeyState[ValidInput::EESC] )
    {
        // Compute the time lap
        double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

        // Execute the game loop
        if ( timeFrame >= gTimeLog )
        {
            update(gKeyState);
            startT = clock();
        }

        // Update the key
        keyUpdate(gKeyState);
        endT = clock();
    }

    system("pause");
    return 0;
}

//******************************************************************
//
// * 偵測輸入狀態
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
    for ( int i = 0; i < ValidInput::INVALID; i++ )
        key[i] = false;

    // Read from input and parse to operation
    /*Please implement your code here*/
    std::string input;
    char command[10] = "";
    int x = 0, y = 0;
    std::getline(std::cin, input);

    if ( input.length() <= 0 )
        return;

    sscanf(input.c_str(), "%[^ ] (%d,%d)", command, &x, &y);
    std::string commandStr = command;

    if ( commandStr == "Jump" )
    {
        key[ValidInput::EJUMP] = true;
        globalJumpX = x;
        globalJumpY = y;
    }
    else if ( commandStr == "Move" )
    {
        int deltaX = x - gHero.getPos().x;
        int deltaY = y - gHero.getPos().y;
        if ( abs(deltaX) <= 1 && abs(deltaY) <= 1 )
        {
            if ( deltaX > 0 )
                key[ValidInput::ED] = true;
            if ( deltaX < 0 )
                key[ValidInput::EA] = true;
            if ( deltaY > 0 )
                key[ValidInput::ES] = true;
            if ( deltaY < 0 )
                key[ValidInput::EW] = true;
        }
    }
    else if ( commandStr == "Exit" )
        key[ValidInput::EESC] = true;
    else
    {
        switch ( *(commandStr.end() - 1) )
        {
        case 'w':
        case 'W':
            key[ValidInput::EW] = true;
            break;
        case 'a':
        case 'A':
            key[ValidInput::EA] = true;
            break;
        case 's':
        case 'S':
            key[ValidInput::ES] = true;
            break;
        case 'd':
        case 'D':
            key[ValidInput::ED] = true;
            break;
        }
    }
    /************************************************************************/
}

//******************************************************************
//
// * 判斷位置是否為空
//==================================================================
bool isPositionValid(Position &pos)
//==================================================================
{
    if ( (pos.x < 0 || pos.x > (GWIDTH - 1)) ||
         (pos.y < 0 || pos.y > (GHEIGHT - 1)) )
        return false;

    // Check whether it is walls
    if ( gBoard[pos.y][pos.x] == GWALL )
        return false;

    return true;
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimun, float maximum)
//==================================================================
{
    return std::max(minimun, std::min(n, maximum));
}

//******************************************************************
//
// * 利用 call-by-referce 將計算得到的方向回傳
//==================================================================
bool canSee(Position cPos, Position hPos, Position &dir)
//==================================================================
{
    // the dir_x and dir_y value are call-by-refernce
    dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
    dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
    int count = 0;
    do
    {
        // spot the target position
        if ( cPos.x + dir.x * count == hPos.x &&
             cPos.y + dir.y * count == hPos.y )
        {
            return true;
        }
        count++;
    } while ( count < gDistance ); // check the range in 4 units
    return false;
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard()
//==================================================================
{
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        for ( int j = 0; j < GWIDTH; j++ )
        {
            if ( i == 0 || i == GHEIGHT - 1 )
            {
                gBoard[i][j] = GWALL;
            }
            else if ( j == 0 || j == GWIDTH - 1 )
            {
                gBoard[i][j] = GWALL;
            }
            else
            {
                gBoard[i][j] = GNOTHING;
            }
        }
    }
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
    // Add the hero into the board
    char drawBoard[GHEIGHT][GWIDTH];

    for ( int i = 0; i < GHEIGHT; i++ )
    {
        for ( int j = 0; j < GWIDTH; j++ )
        {
            drawBoard[i][j] = gBoard[i][j];
        }
    }

    Position t = gTrigger.getPos();
    drawBoard[t.y][t.x] = gTrigger.getIcon();

    Position c = gCreature.getPos();
    drawBoard[c.y][c.x] = gCreature.getIcon();

    // Update the hero information
    Position h = gHero.getPos();
    drawBoard[h.y][h.x] = gHero.getIcon();

    // Draw the board
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        for ( int j = 0; j < GWIDTH; j++ )
        {
            std::cout << drawBoard[i][j]; //  output
        }
        std::cout << "\n";
    }
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
    std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
    std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
    std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
    std::cout << "Every time you step on a trigger T, the hero gets " << gTrigger.getExpAmount() << " EXP points" << std::endl;
    std::cout << "Type Exit to exit" << std::endl;
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
    // 清除版面
    system("CLS");

    // 是否有input
    bool hasInput = false;
    if ( key[ValidInput::EW] )
    {
        gHero.move(0, -1);
        hasInput = true;
    }
    else if ( key[ValidInput::ES] )
    {
        gHero.move(0, 1);
        hasInput = true;
    }
    else if ( key[ValidInput::EA] )
    {
        gHero.move(-1, 0);
        hasInput = true;
    }
    else if ( key[ValidInput::ED] )
    {
        gHero.move(1, 0);
        hasInput = true;
    }
    else if ( key[ValidInput::EJUMP] )
    {
        gHero.jump(globalJumpX, globalJumpY);
        hasInput = true;
    }
    else
    {
        std::cout << "invalid input\n";
    }
    gTrigger.update(gHero);
    gCreature.update(gHero);
    draw();
    drawInfo();
}
