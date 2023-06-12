/**
 *  File: Utilities.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:49:13
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 22:50:53
 *  Description: Utilities Class
 */

#pragma once

#include <SFML/System/Vector2.hpp>
#include <math.h>


namespace Dungeon
{

    class Utilities
    {
    public:
        static sf::Vector2f normalize(sf::Vector2f vec)
        {
            float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y);
            if ( magnitude != 0 )
            {
                vec.x /= magnitude;
                vec.y /= magnitude;
            }
            return vec;
        }
    };

}