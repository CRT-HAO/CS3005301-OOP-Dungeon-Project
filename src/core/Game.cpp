/**
 *  File: Game->cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:36:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 02:48:21
 *  Description: Game Class
 */

#include "core/Game.hpp"

#include "lib/webview/webview.h"

using namespace Dungeon;

Game *Game::instance = nullptr;

Game::Game()
{
    this->w = new webview::webview(true, nullptr);
    int width = 11, height = 11;
    Room *room = new Room(Position(width / -2, height / -2), width, height);
    this->world.addRoom(room);
}

Game *Game::getInstance()
{
    if ( instance == nullptr )
        instance = new Game();

    return instance;
}

void Game::init()
{
    this->w->set_title("Dungeon");
    this->w->set_size(800, 600, WEBVIEW_HINT_NONE);
    this->w->navigate(WebViewUtil::getLocalPath("app.html"));
    this->w->bind("apiUpdate", Game::apiUpdate);
    this->w->bind("apiGetView", Game::apiGetView);
    this->w->bind("apiSetKeyInput", Game::apiSetKeyInput);
}

void Game::runWebView()
{
    this->w->run();
}

void Game::update()
{
    /**
     * Clear View
     */
    this->view.clear();

    KeyInput *keyInputPtr = &this->keyInput;
    View *viewPtr = &this->view;

    // Update camera focus on player
    this->camera.focus(&this->player);

    /**
     * Logic
     */
    this->world.logic(keyInputPtr);
    this->player.logic(keyInputPtr);
    this->camera.logic(keyInputPtr);

    /**
     * Render
     */
    this->world.render(viewPtr);
    this->player.render(viewPtr);
    this->camera.render(viewPtr);
}

std::string Game::apiUpdate(std::string args)
{
    Game *game = Game::getInstance();
    game->update();
    return "\"Success\"";
}

std::string Game::apiGetView(std::string args)
{
    Game *game = Game::getInstance();
    return game->view.data.dump();
}

std::string Game::apiSetKeyInput(std::string args)
{
    Game *game = Game::getInstance();

    Json argsData = Json::parse(args);
    game->keyInput.setKey(argsData[0].get<char>(), argsData[1].get<bool>());

    return "\"Success\"";
}