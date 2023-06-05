/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:14:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 02:32:47
 *  Description: Game Class
 */

#pragma once

#include "../gui/WebViewUtil.hpp"
#include "Camera.hpp"
#include "KeyInput.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "View.hpp"
#include "World.hpp"

#include <string>

namespace webview
{
    class webview;
}

namespace Dungeon
{

    class Game
    {
    private:
        static Game *instance;
        webview::webview *w;
        View view;
        KeyInput keyInput;
        World world;
        Player player{&world};
        Camera camera;

    private:
        Game();

    public:
        static Game *getInstance();

    public:
        void init();
        void runWebView();

    public:
        void update();

    private:
        /**
         * API
         */
        static std::string apiUpdate(std::string args);
        static std::string apiGetView(std::string args);
        static std::string apiSetKeyInput(std::string args);
    };

}