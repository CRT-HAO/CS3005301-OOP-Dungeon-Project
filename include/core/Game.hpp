/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:14:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:27:23
 *  Description: Game Class
 */

#pragma once

#include "Camera.hpp"
#include "KeyInput.hpp"
#include "ObjectManager.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "World.hpp"
#include "core/GUIManager.hpp"
#include "core/GameData.hpp"
#include "core/gui/GameGUI.hpp"
#include "core/gui/PlayerGUI.hpp"

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
        GUIManager guiManager;
        World *world;
        Player *player;
        Camera *camera;
        PlayerGUI playerGUI{nullptr};
        GameGUI gameGUI;

        GameData gameData;
        size_t level{0};

    private:
        Game();

    public:
        static Game *getInstance();

    public:
        void saveFile();
        void loadFile();

    public:
        void init();

    public:
        void update();
        void run();

    public:
        Json toJson() const;
        void fromJson(const Json &json);
    };

}