/**
 *  File: main.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/06/04 04:47:49
 *  Description: 本輸入方向移動功能，w s a d 移動腳色上下左右，
                 空白改變腳色站立之地板字元，到T上可以增加經驗，
                 ESC是離開畫面。同時更新圖版上的資訊。
 */

#include "main.hpp"
#include "Hero.hpp"
#include "creature/CreatureB.hpp"
#include "creature/CreatureS.hpp"

#include <fstream>
#include <string>
#include <vector>

// Icon Settings
const char GWALL = 'O';
const char GNOTHING = ' ';

// Board Settings
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
    ESave = 6,
    ELoad = 7,
    INVALID,
};

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard(int rowN, int colN);
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);
// 遞迴演算法
void CreateMaze(char **board, int x1, int y1, int x2, int y2);

// 程式主驅動函式
void update(bool key[]);

void saveMap();
void loadMap();

Hero gHero(2, 2);
std::vector<ICreature *> gCreatures;
std::vector<IItem *> gItems;

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
        std::cin >> GWIDTH;
        std::cout << "Enter Height: ";
        std::cin >> GHEIGHT;
        system("CLS");
        if ( GHEIGHT < MIN_SIZE || GWIDTH < MIN_SIZE )
        {
            std::cout << "Illegal, both has to be larger than " << MIN_SIZE
                      << std::endl;
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
    // clip the value between -1 ~ 1
    dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f);
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

    /*Please implement your code here*/
    CreateMaze(gBoard, 1, 1, GWIDTH - 2, GHEIGHT - 2);

    // Setup for ( random ) position of all elements and implementation of game
    //     board using 2d dynamic array
    // Elements has to be randomly generated within canvas

    std::vector<std::vector<bool>>
        validFlags(GHEIGHT);
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        validFlags[i].resize(GWIDTH);
        for ( int j = 0; j < GWIDTH; j++ )
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

    // Create Hero
    Position hPos = getValidRandomPos();
    validFlags[hPos.y][hPos.x] = false;
    gHero.setPos(hPos);

    // Create Creature S
    Position csPos = getValidRandomPos();
    validFlags[csPos.y][csPos.x] = false;
    ICreature *creatureS = new CreatureS();
    creatureS->setPos(csPos);
    gCreatures.push_back(creatureS);

    // Create Creature B
    Position cbPos = getValidRandomPos();
    validFlags[cbPos.y][cbPos.x] = false;
    ICreature *creatureB = new CreatureB();
    creatureB->setPos(cbPos);
    gCreatures.push_back(creatureB);

    // Create 2 Triggers
    for ( int i = 0; i < 2; i++ )
    {
        Trigger *trigger = new Trigger();
        Position tPos = getValidRandomPos();
        validFlags[tPos.y][tPos.x] = false;
        trigger->setPos(tPos);
        gItems.push_back(trigger);
    }

    // Create Switch
    Position swPos = getValidRandomPos();
    validFlags[swPos.y][swPos.x] = false;
    IItem *sw = new Switch();
    sw->setPos(swPos);
    gItems.push_back(sw);
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

    std::vector<std::vector<char>> drawBoard(GHEIGHT);

    for ( int i = 0; i < GHEIGHT; i++ )
    {
        drawBoard[i].resize(GWIDTH);
        for ( int j = 0; j < GWIDTH; j++ )
        {
            drawBoard[i][j] = gBoard[i][j];
        }
    }

    // Draw triggers using for loop on drawBoard
    for ( int i = 0; i < gItems.size(); i++ )
    {
        Position t = gItems[i]->getPos();
        drawBoard[t.y][t.x] = gItems[i]->getIcon();
    }

    // Draw creatures using for loop on drawBoard
    for ( int i = 0; i < gCreatures.size(); i++ )
    {
        Position c = gCreatures[i]->getPos();
        drawBoard[c.y][c.x] = gCreatures[i]->getIcon();
    }

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
    std::cout << "The hero is level " << gHero.getLevel()
              << "(" << gHero.getExp() << "/" << gHero.getMaxExp()
              << " to level up)" << std::endl;
    std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
    std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
    std::cout << "Every time you step on a trigger T, the hero gets 10 exp."
              << std::endl;
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
    bool hasInput = false;
    try
    {
        // 是否有input
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
                throw AllInvalid();
        }
    }
    catch ( AllInvalid &a )
    {
        std::cout << a.what() << std::endl;
    }
    if ( hasInput )
    {
        try
        {
            gHero.move(delta);
        }
        catch ( HeroException &e )
        {
            std::cout << e.what() << std::endl;
        }
    }

    // Manipulate update of triggers using while loop
    for ( int i = 0; i < gItems.size(); i++ )
    {
        gItems[i]->update(gHero);
    }

    // Manipulate update of triggers using while loop
    for ( int i = 0; i < gCreatures.size(); i++ )
    {
        gCreatures[i]->update(gHero);
    }
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
    system("CLS");
    std::cout << "Input file name for saving or Exit to leave saving."
              << std::endl;
    std::cout << "Input: ";
    std::string input;
    std::cin >> input;
    if ( input.compare("Exit") == 0 )
        return;

    std::ofstream oStream(input + ".txt");
    oStream << GWIDTH << " " << GHEIGHT << std::endl;

    for ( int i = 0; i < GHEIGHT; i++ )
    {
        for ( int j = 0; j < GWIDTH; j++ )
        {
            oStream << gBoard[i][j];
        }
        oStream << std::endl;
    }
    oStream << std::endl;

    oStream << gHero.getPos() << " " << gHero.getHP() << " "
            << gHero.getLevel() << " " << gHero.getExp() << " "
            << gHero.getMaxExp() << std::endl;

    oStream << gCreatures.size() << std::endl;
    for ( int i = 0; i < gCreatures.size(); i++ )
    {
        oStream << static_cast<int>(gCreatures[i]->getType()) << " "
                << gCreatures[i]->getPos() << std::endl;
    }

    oStream << gItems.size() << std::endl;
    for ( int i = 0; i < gItems.size(); i++ )
    {
        oStream << static_cast<int>(gItems[i]->getType()) << " "
                << gItems[i]->getPos();
        if ( gItems[i]->getType() == TItem::kSwitch )
            oStream << " " << ((Switch *)(gItems[i]))->getOn();
        oStream << std::endl;
    }

    oStream.close();
}

//******************************************************************
//
// * Load the map status
//==================================================================
void loadMap()
{
    // Load from file and reset the dungen
    system("CLS");
    std::cout << "Input file name for loading or Exit to leave loading."
              << std::endl;
    std::cout << "Input: ";
    std::string input;
    std::cin >> input;
    if ( input.compare("Exit") == 0 )
        return;

    std::ifstream iStream(input + ".txt");
    if ( !iStream.is_open() )
        return;

    // reset dungen
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        delete[] gBoard[i];
    }
    delete[] gBoard;

    for ( int i = 0; i < gItems.size(); i++ )
        delete gItems[i];
    gItems.clear();

    for ( int i = 0; i < gCreatures.size(); i++ )
        delete gCreatures[i];
    gCreatures.clear();

    iStream >> GWIDTH >> GHEIGHT;

    char _c;
    iStream.get(_c);

    gBoard = new char *[GHEIGHT];
    for ( int i = 0; i < GHEIGHT; i++ )
    {
        gBoard[i] = new char[GWIDTH];
        for ( int j = 0; j < GWIDTH; j++ )
        {
            iStream.get(gBoard[i][j]);
        }
        iStream.get(_c);
    }

    Position pos;
    int hp, level, exp, maxExp;
    iStream >> pos >> hp >> level >> exp >> maxExp;

    gHero.setPos(pos);
    gHero.setHP(hp);
    gHero.setLevel(level);
    gHero.setExp(exp);
    gHero.SetMaxExp(maxExp);

    int creatureN;
    iStream >> creatureN;
    for ( int i = 0; i < creatureN; i++ )
    {
        int typeN;
        iStream >> typeN;
        TCreature type = static_cast<TCreature>(typeN);
        iStream >> pos;
        ICreature *creature = nullptr;
        switch ( type )
        {
        case TCreature::kS:
        {
            creature = new CreatureS();
            break;
        }
        case TCreature::kB:
        {
            creature = new CreatureB();
            break;
        }
        default:
            throw std::runtime_error("Load File Error: Unknown creature type");
        }
        creature->setPos(pos);
        gCreatures.push_back(creature);
    }

    int triggerN;
    iStream >> triggerN;
    for ( int i = 0; i < triggerN; i++ )
    {
        int typeN;
        iStream >> typeN;
        TItem type = static_cast<TItem>(typeN);
        iStream >> pos;
        IItem *item = nullptr;
        switch ( type )
        {
        case TItem::kSwitch:
        {
            Switch *sw = new Switch();
            bool on = false;
            iStream >> on;
            sw->setOn(on);
            item = sw;
            break;
        }
        case TItem::kTrigger:
        {
            item = new Trigger();
            break;
        }
        default:
            throw std::runtime_error("Load File Error: Unknown item type");
        }
        item->setPos(pos);
        gItems.push_back(item);
    }

    iStream.close();
}

void CreateMaze(char **board, int x1, int y1, int x2, int y2)
{
    if ( (x2 - x1) < 2 || (y2 - y1) < 2 )
    {
        return;
    }

    int x = x1 + 1 + rand() % (x2 - x1 - 1);
    int y = y1 + 1 + rand() % (y2 - y1 - 1);

    for ( int i = x1; i <= x2; i++ )
        gBoard[i][y] = GWALL;
    for ( int i = y1; i <= y2; i++ )
        gBoard[x][i] = GWALL;

    CreateMaze(board, x1, y1, x - 1, y - 1);
    CreateMaze(board, x + 1, y + 1, x2, y2);
    CreateMaze(board, x + 1, y1, x2, y - 1);
    CreateMaze(board, x1, y + 1, x - 1, y2);

    int r[4] = {0};
    r[rand() % 4] = 1;

    for ( int i = 0; i < 4; i++ )
    {
        if ( r[i] == 0 )
        {
            int rx = x;
            int ry = y;
            switch ( i )
            {
            case 0:
                do
                {
                    rx = x1 + rand() % (x - x1);
                } while ( (gBoard[rx - 1][ry] == GWALL) +
                              (gBoard[rx + 1][ry] == GWALL) +
                              (gBoard[rx][ry - 1] == GWALL) +
                              (gBoard[rx][ry + 1] == GWALL) >
                          2 );
                break;

            case 1:
                do
                {
                    ry = y + 1 + rand() % (y2 - y);
                } while ( (gBoard[rx - 1][ry] == GWALL) +
                              (gBoard[rx + 1][ry] == GWALL) +
                              (gBoard[rx][ry - 1] == GWALL) +
                              (gBoard[rx][ry + 1] == GWALL) >
                          2 );
                break;

            case 2:
                do
                {
                    rx = x + 1 + rand() % (x2 - x);
                } while ( (gBoard[rx - 1][ry] == GWALL) +
                              (gBoard[rx + 1][ry] == GWALL) +
                              (gBoard[rx][ry - 1] == GWALL) +
                              (gBoard[rx][ry + 1] == GWALL) >
                          2 );
                break;

            case 3:
                do
                {
                    ry = y1 + rand() % (y - y1);
                } while ( (gBoard[rx - 1][ry] == GWALL) +
                              (gBoard[rx + 1][ry] == GWALL) +
                              (gBoard[rx][ry - 1] == GWALL) +
                              (gBoard[rx][ry + 1] == GWALL) >
                          2 );
                break;

            default:
                break;
            }
            gBoard[rx][ry] = GNOTHING;
        }
    }
}