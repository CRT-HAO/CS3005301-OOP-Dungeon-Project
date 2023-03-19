/*************************************************************************
File:   main.cpp

Author:
        張皓鈞 (B11030202@mail.ntust.edu.tw)
        鄭健廷 (B11130225@mail.ntust.edu.tw)
Comment:
        Draw and print out the canvas.

************************************************************************/

#include <iostream>
#include <stdio.h>

using namespace std;

void drawBoard(bool valid);    // Function to draw board
void makeBoard();              // Function to make board
void modifyBoard(bool &valid); // Function to modify board

const int DUNGEN_ROW = 10, DUNGEN_COL = 20;
char dungenMap[DUNGEN_ROW][DUNGEN_COL];

int main(int argc, char **argv)
{
    bool valid = true;

    makeBoard();
    drawBoard(valid);
    modifyBoard(valid);
    drawBoard(valid);
    return 0;
}

/* Intent: If invalid input then output: "Invalid input" to warn the user
           and output the valid dungeon at last.
   Pre:  Boolen of whether the dungeon is valid.
   Post: Output the last valid dungeon.
         If the modify is invalid, then output the warning words.*/
void drawBoard(bool valid)
//==================================================================
{
    // Draw out the whole board
    /************************************************************************/
    // Identify whether output the warning words.
    if ( !valid )
    {
        cout << "Invalid input" << endl;
    }
    // Output the dungeon
    for ( size_t i = 0; i < DUNGEN_ROW; i++ )
    {
        for ( size_t j = 0; j < DUNGEN_COL; j++ )
        {
            cout << dungenMap[i][j];
        }
        cout << endl;
    }
    /************************************************************************/
}

/* Intent: Make the initial dungeon.
   Pre:  Two char input, one is for symball of wall
         other is for symbal of blank.
   Post: Save the dungeon information into the char array of dungeonMap*/
void makeBoard()
//==================================================================
{
    // Enter symbol for wall and blank then create array
    /************************************************************************/
    char symbalWall, symbalBlank;
    /* Enter two symbols to represent the wall
       and the open space respectively and draw the dungeon wall */
    cout << "Enter symabl for wall: ";
    cin >> symbalWall;
    cout << "Enter symabl for blank: ";
    cin >> symbalBlank;

    // Save the intitial information into the char array dungeonMap
    for ( size_t i = 0; i < DUNGEN_ROW; i++ )
    {
        for ( size_t j = 0; j < DUNGEN_COL; j++ )
        {
            if ( i == 0 || i == DUNGEN_ROW - 1 )
            {
                dungenMap[i][j] = symbalWall;
            }
            else
            {
                if ( j == 0 || j == DUNGEN_COL - 1 )
                {
                    dungenMap[i][j] = symbalWall;
                }
                else
                {
                    dungenMap[i][j] = symbalBlank;
                }
            }
        }
    }
    /************************************************************************/
}

/* Intent: Modify the dungeon if the modification is valid.
   Pre:  Two integer, respectively to the x and y position of the modification.
         One char for the symabl of modification.
         One boolen for record whether the modification is valid.
   Post: Modify the dungeon if the modification is valid,
         otherwise don't modify the dungeon, and record the boolen valid to false.*/
void modifyBoard(bool &valid)
//==================================================================
{
    // Function for modifying board given position and char to change
    /************************************************************************/
    int x = 0, y = 0;
    char symbalModify;
    // Place the specified symbol anywhere in the specified dungeon by entering
    cout << "Enter symabl for modifying position: ";
    cin >> symbalModify;
    cout << "Enter X of modifying position: ";
    cin >> x;
    cout << "Enter Y of modifying position: ";
    cin >> y;
    // Identify whether the input modification is valid, if valid then modify.
    if ( (x > 0 && x < DUNGEN_COL - 1) && (y > 0 && y < DUNGEN_ROW - 1) )
    {
        valid = true;
        dungenMap[y][x] = symbalModify;
    }
    else
    {
        valid = false;
    }
    /************************************************************************/
}