/**
 *  File: Trigger.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 17:49:48
 *  Description: Trigger Class
 */

#include "Trigger.hpp"

void Trigger::update(Hero &hero) const
{
    if ( hero.getPos().x == _pos.x && hero.getPos().y == _pos.y )
    {
        hero.gainEXP(_exp);
    }
}