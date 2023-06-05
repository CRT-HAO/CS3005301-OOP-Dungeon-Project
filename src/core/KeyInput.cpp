/**
 *  File: KeyInput.cp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 19:50:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/05 19:57:11
 *  Description: Key Input Class
 */

#include "core/KeyInput.hpp"

using namespace Dungeon;

KeyInput::KeyInput()
{
    this->clear();
}

void KeyInput::clear()
{
    for ( uint8_t i = 0; i < 255; ++i )
        this->keys[i] = false;
}