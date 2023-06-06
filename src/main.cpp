/**
 *  File: main.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/20 17:54:59
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 15:50:13
 *  Description: Program Entry Point
 */

#include "core/Game.hpp"

#include <iostream>

using namespace std;
using namespace Dungeon;

int main(int argc, char *argv[])
{
    Game::getInstance()->init();
    Game::getInstance()->run();

    return 0;
}