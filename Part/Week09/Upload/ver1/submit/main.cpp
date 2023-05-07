/**
 *  File: main.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/06 10:56:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/07 02:51:52
 *  Description: 基本輸入方向移動功能，w s a d 移動腳色上下左右，
 *               空白改變腳色站立之地板字元，到T上可以增加經驗，
 *               ESC是離開畫面。同時更新圖版上的資訊。
 */

#include "main.h"
#include "Hero.h"

#include <fstream>
#include <vector>

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
            std::cout << "Creature has find the Hero in the ( "
                      << dir.x << ", " << dir.y << " ) direction\n";
            this->sIcon = '!';
        }
        else
        {
            std::cout << "Creature didn't find the Hero\n";
            this->sIcon = 'C';
        }

        if ( !(hPos != sPos) )
        {
            hero.damage(power);
        }
    }
};

// Canva Icon
const char GWALL = 'O';
const char GNOTHING = ' ';

int gWidth = -1;
int gHeight = -1;
const int GMIN_SIZE = 4;
const double GTIME_LOG = 0.033;

// Distance
const int GDISTANCE = 4;

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
    ESave = 6,
    ELoad = 7,
    INVALID,
};

Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard(int rowN, int colN);
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

void saveMap();
void loadMap();

std::vector<Trigger *> gTriggers;

int main(int argc, char **argv)
{
    srand(time(NULL));

    // 用來管理鍵盤輸入狀態的陣列
    bool gKeyState[ValidInput::INVALID];
    for ( int i = 0; i < ValidInput::INVALID; i++ )
    {
        gKeyState[i] = false;
    }

    while ( true )
    {
        std::cout << "Enter Width: ";
        std::cin >> gWidth;
        std::cout << "Enter Height: ";
        std::cin >> gHeight;
        system("CLS");
        if ( gHeight < GMIN_SIZE || gWidth < GMIN_SIZE )
        {
            std::cout << "Illegal, both has to be larger than "
                      << GMIN_SIZE << std::endl;
        }
        else
            break;
    }

    // Setup a clear dungeon
    setupBoard(gHeight, gWidth);

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
        if ( timeFrame >= GTIME_LOG )
        {
            update(gKeyState);
            startT = clock();
        }

        // Update the key
        keyUpdate(gKeyState);
        endT = clock();

        if ( gKeyState[ValidInput::ESave] )
        {
            saveMap();
            gKeyState[ValidInput::ESave] = false;
        }
        else if ( gKeyState[ValidInput::ELoad] )
        {
            loadMap();
            gKeyState[ValidInput::ELoad] = false;
        }
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
    case '1':
        key[ValidInput::ESave] = true;
        break;
    case '2':
        key[ValidInput::ELoad] = true;
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
    // Check whether it is an empty space
    if ( gBoard[pos.y][pos.x] != GNOTHING )
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
        if ( cPos + dir * count == hPos )
        {
            return true;
        }
        count++;
    } while ( count < GDISTANCE ); // check the range in 4 units
    return false;
}

//******************************************************************
//
// * Setup the blank board
//==================================================================
void setupBlankBoard(int rowN, int colN)
//==================================================================
{
    // Allocate & init game board using 2d dynamic array

    gBoard = new char *[rowN];
    for ( int i = 0; i < rowN; i++ )
    {
        gBoard[i] = new char[colN];
        for ( int j = 0; j < colN; j++ )
        {
            if ( i == 0 || i == rowN - 1 || j == 0 || j == colN - 1 )
                gBoard[i][j] = GWALL;
            else
                gBoard[i][j] = GNOTHING;
        }
    }
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard(int rowN, int colN)
//==================================================================
{
    // Allocate & init game board using 2d dynamic array

    setupBlankBoard(rowN, colN);

    // Setup for (random) position of all elements and implementation of
    // game board using 2d dynamic array
    // Elements has to be randomly generated within canvas

    std::vector<std::vector<bool>> validFlags(gHeight);
    for ( int i = 0; i < gHeight; i++ )
    {
        validFlags[i].resize(gWidth);
        for ( int j = 0; j < gWidth; j++ )
        {
            validFlags[i][j] = gBoard[i][j] == GWALL ? false : true;
        }
    }

    auto getRandomPos = [&rowN, &colN]()
    {
        return Position((int)(rand() % colN), (int)(rand() % rowN));
    };

    auto getValidRandomPos = [&validFlags, &getRandomPos]()
    {
        while ( true )
        {
            Position pos = getRandomPos();
            if ( validFlags[pos.y][pos.x] )
            {
                return pos;
            }
        }
    };

    Position hPos = getValidRandomPos();
    validFlags[hPos.y][hPos.x] = false;
    gHero.setPos(hPos);

    Position cPos = getValidRandomPos();
    validFlags[cPos.y][cPos.x] = false;
    gCreature.setPos(cPos);

    for ( int i = 0; i < 2; i++ )
    {
        Trigger *trigger = new Trigger();
        Position tPos = getValidRandomPos();
        validFlags[tPos.y][tPos.x] = false;
        trigger->setPos(tPos);
        gTriggers.push_back(trigger);
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
    // Setup and implementation of drawing board using 2d vector

    std::vector<std::vector<char>> drawBoard(gHeight);

    for ( int i = 0; i < gHeight; i++ )
    {
        drawBoard[i].resize(gWidth);
        for ( int j = 0; j < gWidth; j++ )
        {
            drawBoard[i][j] = gBoard[i][j];
        }
    }

    // Draw two triggers using for loop on drawBoard

    for ( int i = 0; i < gTriggers.size(); i++ )
    {
        Position t = gTriggers[i]->getPos();
        drawBoard[t.y][t.x] = gTriggers[i]->getIcon();
    }

    Position c = gCreature.getPos();
    drawBoard[c.y][c.x] = gCreature.getIcon();

    // Update the hero information
    Position h = gHero.getPos();
    drawBoard[h.y][h.x] = gHero.getIcon();

    // Draw the board
    for ( int i = 0; i < gHeight; i++ )
    {
        for ( int j = 0; j < gWidth; j++ )
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
    std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
    std::cout << "(ESC) Exit (1) Save (2) Load" << std::endl;
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

    Position delta;

    // 是否有input
    bool hasInput = false;
    if ( key[ValidInput::EW] )
    {
        delta -= Position(0, 1);
        hasInput = true;
    }
    else if ( key[ValidInput::ES] )
    {
        delta += Position(0, 1);
        hasInput = true;
    }
    else if ( key[ValidInput::EA] )
    {
        delta = delta - Position(1, 0);
        hasInput = true;
    }
    else if ( key[ValidInput::ED] )
    {
        delta = delta + Position(1, 0);
        hasInput = true;
    }
    else
    {
        bool allInvalid = true;
        for ( int i = 0; i < ValidInput::INVALID; i++ )
        {
            if ( key[i] )
            {
                allInvalid = false;
                break;
            }
        }
        if ( allInvalid )
            std::cout << "invalid input\n";
    }
    if ( hasInput )
    {
        gHero.move(delta);
    }

    // Manipulate update of two triggers using while loop

    for ( int i = 0; i < gTriggers.size(); i++ )
    {
        gTriggers[i]->update(gHero);
    }

    gCreature.update(gHero);
    draw();
    drawInfo();
}

//******************************************************************
//
// * Save the map status
//==================================================================
void saveMap()
{
    // Save dungen to file
    /*Please implement your code here*/
    // Save format:
    //  canvas_width canvas_height
    //  canvas_icon_wall canvas_icon_nothing
    //  hero_pos_x hero_pos_y hero_icon hero_hp hero_level hero_exp hero_maxexp
    //  creature_pos_x creature_y creature_icon
    //  triggers_number
    //  trigger_pos_x trigger_pos_y trigger_icon
    //  trigger_pos_x trigger_pos_y trigger_icon

    std::ofstream ofs;
    std::string filename;
    std::cout << "Input file name for saving or Exit to leave saving."
              << std::endl;
    std::cout << "Input: ";
    std::cin >> filename;
    ofs.open(filename);
    if ( !ofs.is_open() )
    {
        std::cout << "Error: open " << filename << " error." << std::endl;
        return;
    }

    ofs << gWidth << ' ' << gHeight << std::endl
        << int(GWALL) << ' ' << int(GNOTHING) << std::endl
        << gHero.getPos().x << ' ' << gHero.getPos().y << ' '
        << int(gHero.getIcon()) << ' ' << gHero.getHP() << ' '
        << gHero.getLevel() << ' ' << gHero.getExp() << ' '
        << gHero.getMaxExp() << std::endl
        << gCreature.getPos().x << ' ' << gCreature.getPos().y << ' '
        << int(gCreature.getIcon()) << std::endl
        << gTriggers.size() << std::endl;
    for ( const auto t : gTriggers )
        ofs << t->getPos().x << ' ' << t->getPos().y << ' ' << int(t->getIcon())
            << std::endl;
    /************************************************************************/
}

//******************************************************************
//
// * Load the map status
//==================================================================
void loadMap()
{
    // Load from file and reset the dungen
    /*Please implement your code here*/
    std::ifstream ifs;
    std::string filename;
    std::cout << "Input file name for loading or Exit to leave loading."
              << std::endl;
    std::cout << "Input: ";
    std::cin >> filename;
    ifs.open(filename);
    if ( !ifs.is_open() )
    {
        std::cout << "Error: open " << filename << " error." << std::endl;
        return;
    }

    // Canvas
    int canvasIconWall, canvasIconNothing;
    ifs >> gWidth >> gHeight;
    ifs >> canvasIconWall >> canvasIconNothing;
    setupBlankBoard(gHeight, gWidth);

    // Hero
    int heroPosX, heroPosY, heroHP, heroLevel, heroExp, heroMaxExp;
    int heroIcon;
    ifs >> heroPosX >> heroPosY >> heroIcon;
    ifs >> heroHP >> heroLevel >> heroExp >> heroMaxExp;
    char heroIconChar = static_cast<char>(heroIcon);
    gHero.setPos(Position(heroPosX, heroPosY));
    gHero.setIcon(heroIconChar);
    gHero.setLevel(heroLevel);
    gHero.setHP(heroHP);
    gHero.setExp(heroExp);
    gHero.SetMaxExp(heroMaxExp);

    // Creature
    int creaturePosX, creaturePosY;
    int creatureIcon;
    ifs >> creaturePosX >> creaturePosY >> creatureIcon;
    char creatureIconChar = static_cast<char>(creatureIcon);
    gCreature.setPos(Position(creaturePosX, creaturePosY));
    gCreature.setIcon(creatureIconChar);

    // Triggers
    // Delete all triggers first
    for ( auto t : gTriggers )
        delete t;
    gTriggers.clear();

    size_t triggersNums;
    ifs >> triggersNums;

    for ( size_t i = 0; i < triggersNums; ++i )
    {
        int triggerPosX, triggerPosY;
        int triggerIcon;
        ifs >> triggerPosX >> triggerPosY >> triggerIcon;
        Trigger *t = new Trigger(triggerPosX, triggerPosY);
        gTriggers.push_back(t);
    }
    /************************************************************************/
}
