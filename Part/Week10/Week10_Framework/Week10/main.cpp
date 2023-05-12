/**
 *  File: main.cpp
 *  Author: ?i?q?v (B11030202@mail.ntust.edu.tw)
 *  Author: ?G???? (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/12 16:44:27
 *  Description: ????J??V????\??Aw s a d ????}??W?U???k?A
                 ??????}??????a?O?r???A??T?W?i?H?W?[?g??A
                 ESC?O???}?e???C?P???s????W????T?C
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

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

int GWIDTH = -1;
int GHEIGHT = -1;
const int MIN_SIZE = 4;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// ?�Z??x?s???????
char **gBoard;

// ?w?q?????J???O?P?????}?Cindex
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
// ??????J???A
void keyUpdate(bool key[]);
// ??l?????
void setupBoard(int rowN, int colN);
// ??X????
void draw(void);
// ??X??????T
void drawInfo(void);
// void randommap(int x, int y, int height, int width);
// void openAdoor(int x1, int y1, int x2, int y2);

// ?{???D?X??��
void update(bool key[]);

void saveMap();
void loadMap();
void randomWall(int x, int y, int width, int height, bool orientation);

std::vector<Trigger *> gTriggers;

int main(int argc, char **argv)
{
    srand(time(NULL));

    // ?�Z??z??L??J???A???}?C
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
// * ??????J???A
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
// * ?P?_??m?O?_????
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
// * ?Q?? call-by-referce ?N?p??o????V?^??
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
    // int startX = rand() % (rowN - 2) + 1;
    // int startY = rand() % (colN - 2) + 1;

    // randommap(startX, startY, colN, rowN);
    /*Please implement your code here*/
    int g = rand();
    randomWall(0, 0, GWIDTH, GHEIGHT, g % 2);

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

    std::vector<std::vector<char>> drawBoard(GHEIGHT);

    for ( int i = 0; i < GHEIGHT; i++ )
    {
        drawBoard[i].resize(GWIDTH);
        for ( int j = 0; j < GWIDTH; j++ )
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
    // ?M??????
    system("CLS");

    Position delta;

    // ?O?_??input
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
        ;
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
    oStream << gCreature.getPos() << std::endl;
    oStream << gTriggers.size() << std::endl;
    for ( int i = 0; i < gTriggers.size(); i++ )
    {
        oStream << gTriggers[i]->getPos() << std::endl;
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

    for ( int i = 0; i < gTriggers.size(); i++ )
        delete gTriggers[i];
    gTriggers.clear();

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

    iStream >> pos;
    gCreature.setPos(pos);

    int triggerN;
    iStream >> triggerN;
    for ( int i = 0; i < triggerN; i++ )
    {
        iStream >> pos;
        Trigger *trigger = new Trigger();
        trigger->setPos(pos);
        gTriggers.push_back(trigger);
    }

    iStream.close();
}

// void randommap(int x, int y, int height, int width)
// {
//     int posX, posY;

//     if ( height <= 2 || width <= 2 )
//         return;

//     posX = (rand() % (height / 2)) * 2 + 1;
//     for ( size_t i = 0; i < width; i++ )
//     {
//         gBoard[posX][i] = GWALL;
//     }

//     posY = (rand() % (width / 2)) * 2 + 1;
//     for ( size_t i = 0; i < height; i++ )
//     {
//         gBoard[i][posY] = GWALL;
//     }

//     int isClosed = (rand() % 4) + 1;
//     switch ( isClosed )
//     {
//     case 1:
//         openAdoor(posX + 1, posY, x + height - 1, posY);
//         openAdoor(posX, posY + 1, posX, y + width - 1);
//         openAdoor(x, posY, posX - 1, posY);
//         break;

//     case 2:
//         openAdoor(posX, posY + 1, posX, y + width - 1);
//         openAdoor(x, posY, posX - 1, posY);
//         openAdoor(posX, y, posX, posY - 1);
//         break;

//     case 3:
//         openAdoor(x, posY, posX - 1, posY);
//         openAdoor(posX, y, posX, posY - 1);
//         openAdoor(posX + 1, posY, x + height - 1, posY);
//         break;

//     case 4:
//         openAdoor(posX, y, posX, posY - 1);
//         openAdoor(posX + 1, posY, x + height - 1, posY);
//         openAdoor(posX, posY + 1, posX, y + width - 1);
//         break;

//     default:
//         break;
//     }
//     randommap(x, y, posX - x, posY - y);
//     randommap(x, posY + 1, posX - x, width - posY + y - 1);
//     randommap(posX + 1, y, height - posX + x - 1, posY - y);
//     randommap(posX + 1, posY + 1,
//               height - posX + x - 1, width - posY + y - 1);
// }

// void openAdoor(int x1, int y1, int x2, int y2)
// {
//     int pos;
//     if ( x1 == x2 )
//     {
//         pos = y1 + (rand() % ((y2 - y1) / 2 + 1)) * 2;
//         gBoard[x1][pos] = GNOTHING;
//     }
//     else if ( y1 == y2 )
//     {
//         pos = x1 + (rand() % ((x2 - x1) / 2 + 1)) * 2;
//         gBoard[pos][y1] = GNOTHING;
//     }
// }

// orientation false == vertical;true == horizontal
void randomWall(int x, int y, int width, int height, bool orientation)
{

    x++, y++, width -= 2, height -= 2;
    if ( width <= 2 || height <= 2 )
        return;

    unsigned int wallHoleX, wallHoleY;

    // Calcaulate where the wall hole will be
    wallHoleX = x + (rand() % (width - (orientation ? 0 : 2)) +
                     (orientation ? 0 : 1));
    wallHoleY = y + (rand() % (height - (orientation ? 2 : 0)) +
                     (orientation ? 1 : 0));

    // Draw the wall with hole
    // std::cout << wallHoleX << " " << wallHoleY << std::endl;

    for ( size_t i = (orientation ? x : y);
          i < (orientation ? width : height) + 1; i++ )
    {
        if ( orientation )
        {
            if ( i != wallHoleX )
                gBoard[wallHoleY][i] = GWALL;
        }
        else
        {
            if ( i != wallHoleY )
                gBoard[i][wallHoleX] = GWALL;
        }
    }

    x--, y--, width += 2, height += 2;
    randomWall(x, y, wallHoleX + 1, wallHoleY + 1, !orientation);
    randomWall(wallHoleX, y, width - wallHoleX,
               wallHoleY + 1, !orientation);
    randomWall(x, wallHoleY, wallHoleX + 1,
               height - wallHoleY, !orientation);
    randomWall(wallHoleX, wallHoleY, width - wallHoleX,
               height - wallHoleY, !orientation);
}