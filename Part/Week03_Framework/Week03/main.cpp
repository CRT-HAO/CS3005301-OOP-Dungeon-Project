/************************************************************************
File:   Source.cpp

Author:
        ���s�Aea5878158@gmail.com
Modifier:
        �௧�N�Acheeryuchi@gmail.com
        �U��ģ�Aguweiyao867@gmail.com
        ���T�t�AJYCReports@gmail.com
        ���ſ��Atbcey74123@gmail.com
Comment:
        Draw and print out the canvas.

************************************************************************/

#include <iostream>
#include <stdio.h>
using namespace std;

void drawBoard(bool valid);                               // Function to draw board
void makeBoard(char symbalWall, char symbalBlank);        // Function to make board
void modifyBoard(int x, int y, char symbal, bool &valid); // Function to modify board

const int DUNGEN_ROW = 10, DUNGEN_COL = 20;
char dungenMap[DUNGEN_ROW][DUNGEN_COL];

int main(int argc, char **argv)
{
    int x = 0, y = 0;
    char symbalWall, symbalBlank, symbalModify;
    bool valid = true;
    cout << "Enter symabl for wall: ";
    cin >> symbalWall;
    cout << "Enter symabl for blank: ";
    cin >> symbalBlank;
    makeBoard(symbalWall, symbalBlank);
    drawBoard(valid);
    cout << "Enter symabl for modifying position: ";
    cin >> symbalModify;
    cout << "Enter X of modifying position: ";
    cin >> x;
    cout << "Enter Y of modifying position: ";
    cin >> y;
    modifyBoard(x, y, symbalModify, valid);
    drawBoard(valid);
}

void drawBoard(bool valid)
//==================================================================
{
    // Draw out the whole board
    /************************************************************************/
    if ( !valid )
    {
        cout << "Invalid input" << endl;
    }
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

void makeBoard(char symbalWall, char symbalBlank)
//==================================================================
{
    // Enter symbol for wall and blank then create array
    /************************************************************************/
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

void modifyBoard(int x, int y, char symbal, bool &valid)
//==================================================================
{
    // Function for modifying board given position and char to change
    /************************************************************************/
    if ( (x > 0 && x < DUNGEN_COL - 1) && (y > 0 && y < DUNGEN_ROW - 1) )
    {
        valid = true;
        dungenMap[y][x] = symbal;
    }
    else
    {
        valid = false;
    }
    /************************************************************************/
}