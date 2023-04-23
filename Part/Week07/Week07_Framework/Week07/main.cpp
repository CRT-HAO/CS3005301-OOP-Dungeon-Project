/**
 *  File: main.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/23 09:17:14
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023-04-23 19:46:57
 *  Description: 基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，
 *               到T上可以增加經驗ESC是離開畫面。同時更新圖版上的資訊。
 */

#include "main.h"

#include <random>
#include <vector>

#include "Hero.h"

Hero gHero(2, 2);

class Creature
{ // creature class
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

int GWIDTH = -1;
int GHEIGHT = -1;
const int MIN_SIZE = 4;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char **gBoard;

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
    EW = 0,
    ES = 1,
    EA = 2,
    ED = 3,
    ESPACE = 4,
    EESC = 5,
    INVALID,
};

Creature gCreature;

// Create vector of trigger pointer for further managenent and manipulation
/*Please implement your code here*/
std::vector<Trigger *> triggers;
/************************************************************************/

int main(int argc, char **argv)
{
    srand(time(NULL));

    // 用來管理鍵盤輸入狀態的陣列
    bool gKeyState[6];
    for ( int i = 0; i < 6; i++ )
    {
        gKeyState[i] = false;
    }

    while ( true )
    {
        std::cout << "Enter Width: ";
        std::cin >> GWIDTH;
        std::cout << "Enter Height: ";
        std::cin >> GHEIGHT;
        system("CLS");
        if ( GHEIGHT < MIN_SIZE || GWIDTH < MIN_SIZE )
        {
            std::cout << "Illegal, both has to be larger than " << MIN_SIZE << std::endl;
        }
        else
        {
            break;
        }
    }

    // Setup a clear dungeon
    setupBoard(GHEIGHT, GWIDTH);

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
    {
        key[i] = false;
    }
    char input = _getch();
    switch ( input )
    {
    case 'w':
        key[ValidInput::EW] = true;
        break;
    case 's':
        key[ValidInput::ES] = true;
        break;
    case 'a':
        key[ValidInput::EA] = true;
        break;
    case 'd':
        key[ValidInput::ED] = true;
        break;
    case ' ':
        key[ValidInput::ESPACE] = true;
        break;
    case 27:
        key[ValidInput::EESC] = true;
        break;
    default:
        break;
    }
}

//******************************************************************
//
// * 判斷位置是否為空
//==================================================================
bool isPositionValid(Position &pos)
//==================================================================
{
    // // Check whether it is an empty space
    // if (gBoard[pos.y][pos.x] != GNOTHING)
    //   return false;

    // return true;
    return (gBoard[pos.y][pos.x] != GWALL);
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
void setupBoard(int rowN, int colN)
//==================================================================
{
    // Allocate & init game board using 2d dynamic array
    /*Please implement your code here*/

    /************************************************************************/

    // Setup for (random) position of all elements and implementation of game board using 2d dynamic array
    // Elements has to be randomly generated within canvas
    // Two triggers should also be initialized and pushed to the container here.
    /*Please implement your code here*/

    gBoard = new char *[rowN];
    for ( int i = 0; i < rowN; i++ )
    {
        gBoard[i] = new char[colN];
        for ( int j = 0; j < colN; j++ )
            gBoard[i][j] = GNOTHING;
    }

    for ( int i = 0; i < rowN; i++ )
        gBoard[i][0] = GWALL;

    for ( int i = 0; i < rowN; i++ )
        gBoard[i][colN - 1] = GWALL;

    for ( int i = 0; i < colN; i++ )
        gBoard[0][i] = GWALL;

    for ( int i = 0; i < colN; i++ )
        gBoard[rowN - 1][i] = GWALL;

    triggers.push_back(new Trigger());
    triggers.push_back(new Trigger());

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni_x(0, GWIDTH - 1);
    std::uniform_int_distribution<int> uni_y(0, GHEIGHT - 1);

    for ( size_t i = 0; i < triggers.size(); )
    {
        int x = uni_x(rng);
        int y = uni_y(rng);
        if ( gBoard[y][x] == GNOTHING )
        {
            triggers[i]->setPos(x, y);
            gBoard[y][x] = triggers[i]->getIcon();
            i += 1;
        }
    }

    for ( bool findPos = false; !findPos; )
    {
        int x = uni_x(rng);
        int y = uni_y(rng);
        if ( gBoard[y][x] == GNOTHING )
        {
            gCreature.setPos(x, y);
            gBoard[y][x] = gCreature.getIcon();
            findPos = true;
        }
    }

    for ( bool findPos = false; !findPos; )
    {
        int x = uni_x(rng);
        int y = uni_y(rng);
        if ( gBoard[y][x] == GNOTHING )
        {
            gHero.setPos(x, y);
            gBoard[y][x] = gHero.getIcon();
            findPos = true;
        }
    }

    /************************************************************************/
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
    // Add the hero into the board
    // Setup and implementation of drawing board using 2d vector
    /*Please implement your code here*/
    std::vector<std::vector<char>> drawBoard(GHEIGHT, std::vector<char>(GWIDTH, ' '));
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        for ( int j = 0; j < GWIDTH; j++ )
        {
            if ( gBoard[i][j] == GWALL )
                drawBoard[i][j] = GWALL;
        }
    }
    /************************************************************************/

    // Draw two triggers using for loop on drawBoard
    /*Please implement your code here*/
    for ( Trigger *i : triggers )
    {
        Position p = i->getPos();
        drawBoard[p.y][p.x] = i->getIcon();
    }
    /************************************************************************/

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
        std::cout << std::endl;
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
    std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
    std::cout << "Press ESC key to exit" << std::endl;
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
    else
    {
        std::cout << "invalid input\n";
    }

    // Manipulate update of two triggers using while loop
    /*Please implement your code here*/
    for ( Trigger *t : triggers )
    {
        t->update(gHero);
    }
    /************************************************************************/

    gCreature.update(gHero);
    draw();
    drawInfo();
}
