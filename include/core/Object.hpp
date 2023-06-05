/**
 *  File: Object.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 22:59:50
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/05 20:24:39
 *  Description: Object Class
 */

#pragma once

#include "KeyInput.hpp"
#include "View.hpp"

namespace Dungeon
{

    class Object
    {
    public:
        ~Object() = default;

    public:
        virtual void logic(KeyInput *keyInput) = 0;
        virtual void render(View *view) = 0;
    };

}