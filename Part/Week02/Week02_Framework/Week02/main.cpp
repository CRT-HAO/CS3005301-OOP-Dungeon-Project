/************************************************************************
File:   main.cpp

Author:
        張皓鈞 (B11030202@mail.ntust.edu.tw)
        鄭健廷 (B11130225@mail.ntust.edu.tw)
Comment:
        Output character position after W,A,S,D input.
        Output invalid if destination out of boundary.
        ESC to stop process.

************************************************************************/
#include <conio.h>  // For getch() function
#include <iostream> // For print out information

using namespace std;

bool tryMove(int deltaX, int deltaY);
bool checkValidDst(int x, int y);

// Define inputs and its index
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

// Detect state of input
void keyUpdate(bool key[]);

int posX = 0, posY = 0;    // global param to keep the character position
const int DUNGEN_SIZE = 5; // For each dimension, -DUNGEN_SIZE < pos < DUNGEN_SIZE

int main()
{
    // Obtain and update the input using a loop
    for ( ;; )
    {
        // Initialize state of key
        bool gKeyState[ValidInput::INVALID];

        keyUpdate(gKeyState);

        int deltaX = 0, deltaY = 0;

        if ( gKeyState[ValidInput::EW] )
            deltaY += 1;

        if ( gKeyState[ValidInput::EA] )
            deltaX += -1;

        if ( gKeyState[ValidInput::ES] )
            deltaY += -1;

        if ( gKeyState[ValidInput::ED] )
            deltaX += 1;

        if ( gKeyState[ValidInput::EESC] )
        {
            cout << "Key ESC is pressed. End program." << endl;
            return 0;
        }

        if ( tryMove(deltaX, deltaY) )
            printf("Character position:(%d,%d)\n", posX, posY);
        else
            cout << "Failed to move\n";
    }

    return 0;
}

//******************************************************************
//
// * Move character with input delta, return true if successful otherwise false
//==================================================================
bool tryMove(int deltaX, int deltaY)
{
    /************************************************************************/
    /*Please implement your code here*/
    bool t = checkValidDst(posX + deltaX, posY + deltaY);
    if ( t )
    {
        posX += deltaX;
        posY += deltaY;
    }
    return t;
}

//******************************************************************
//
// * Check if given position is a valid destination, return true if valid otherwise false
//==================================================================
bool checkValidDst(int x, int y)
{
    return (x < DUNGEN_SIZE && -DUNGEN_SIZE < x && y < DUNGEN_SIZE && -DUNGEN_SIZE < y);
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

    // Implement a switch for output calls
    switch ( input )
    {
    case 'W':
    case 'w':
        key[ValidInput::EW] = true;
        break;

    case 'A':
    case 'a':
        key[ValidInput::EA] = true;
        break;

    case 'S':
    case 's':
        key[ValidInput::ES] = true;
        break;

    case 'D':
    case 'd':
        key[ValidInput::ED] = true;
        break;

    case ' ':
        key[ValidInput::ESPACE] = true;
        break;

    case 27: // ESC
        key[ValidInput::EESC] = true;
        break;
    }
}