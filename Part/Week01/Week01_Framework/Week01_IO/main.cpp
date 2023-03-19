/**
 * @ Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 * @ Create Time: 2023-02-21 19:52:33
 * @ Modified by: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 * @ Modified time: 2023-03-20 00:16:03
 * @ Description: Output W,A,S,D after input, ESC to stop process.
 */

#include <conio.h> // For getch() function

#include <iostream> // For print out information

using namespace std;

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

int main()
{
    // Initialize state of key
    bool gKeyState[ValidInput::INVALID];

    // Obtain and update the input using a loop
    for ( ;; )
    {
        keyUpdate(gKeyState);

        if ( gKeyState[ValidInput::EW] )
        {
            cout << "Key W is pressed." << endl;
        }

        if ( gKeyState[ValidInput::EA] )
        {
            cout << "Key A is pressed." << endl;
        }

        if ( gKeyState[ValidInput::ES] )
        {
            cout << "Key S is pressed." << endl;
        }

        if ( gKeyState[ValidInput::ED] )
        {
            cout << "Key D is pressed." << endl;
        }

        if ( gKeyState[ValidInput::EESC] )
        {
            cout << "Key ESC is pressed. End program." << endl;
            break;
        }
    }

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
