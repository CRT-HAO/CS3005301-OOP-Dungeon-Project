/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:14:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 01:06:49
 *  Description: Game Class
 */

#pragma once

#include "Camera.hpp"
#include "KeyInput.hpp"
#include "ObjectManager.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "World.hpp"

#include <SFML/Graphics.hpp>

#include <string>

namespace Dungeon
{

    class Game
    {
    private:
        static Game *instance;

        sf::RenderWindow window;
        sf::View view;
        sf::Clock clock;
        sf::Time dt;

        KeyInput keyInput;

        ObjectManager objectManager;
        World world;
        Player player{&world};
        Camera camera;

    private:
        Game();

    public:
        static Game *getInstance();

    public:
        void init();

    public:
        void update();
        void run();
    };

}