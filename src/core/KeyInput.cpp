/**
 *  File: KeyInput.cp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 19:50:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 16:12:05
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
    for ( int i = sf::Keyboard::Key::Unknown; i < sf::Keyboard::Key::Return; ++i )
        this->keys[static_cast<sf::Keyboard::Key>(i)] = false;
}