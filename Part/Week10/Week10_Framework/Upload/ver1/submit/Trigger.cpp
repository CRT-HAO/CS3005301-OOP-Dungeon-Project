/**
 *  File: Trigger.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/11 00:54:01
 *  Description: Trigger Class
 */

#include "Trigger.h"

void Trigger::update(Hero &hero) const
{
    if ( hero.getPos().x == _pos.x && hero.getPos().y == _pos.y )
    {
        hero.gainEXP(_exp);
    }
}