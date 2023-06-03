/**
 *  File: Hero.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/06/04 00:59:02
 *  Description: Hero Class
 */

#include "Hero.hpp"

void Hero::move(Position delta)
{
    // Compute the next position
    Position next = this->sPos + delta;

    if ( isPositionValid(next) )
        this->sPos = next;
    else
    {
        throw HeroException();
    }
}