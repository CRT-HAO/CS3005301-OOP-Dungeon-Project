/**
 *  File: main.cpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Create Date: 2023/03/20 00:08:21
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/03/20 00:27:35
 *  Description: Draw and print out the canvas.
 */

#include <iostream>
#include <stdio.h>

using namespace std;

void drawBoard();              // Function to draw board
void makeBoard();              // Function to make board
void modifyBoard(bool &valid); // Function to modify board

const int DUNGEN_ROW = 10, DUNGEN_COL = 20;
char dungenMap[DUNGEN_ROW][DUNGEN_COL];

int main(int argc, char **argv)
{

    makeBoard();
    drawBoard();
    bool valid = true;
    modifyBoard(valid);
    // Print error if modify board fail
    if ( !valid )
    {
        cout << "Invalid input" << endl;
    }
    drawBoard();
    return 0;
}

/* Intent: Output the valid dungeon at last.
   Post: Output the last valid dungeon.*/
void drawBoard()
//==================================================================
{
    // Draw out the whole board
    /************************************************************************/
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
   Pre: One boolen for record whether the modification is valid.
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
    valid = (x > 0 && x < DUNGEN_COL - 1) && (y > 0 && y < DUNGEN_ROW - 1);
    if ( valid )
        dungenMap[y][x] = symbalModify;
    /************************************************************************/
}