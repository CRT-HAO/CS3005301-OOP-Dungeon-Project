/**
 *  File: Game->cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:36:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 17:07:01
 *  Description: Game Class
 */

#include "core/Game.hpp"

using namespace Dungeon;

Game *Game::instance = nullptr;

Game::Game()
{
    int width = 41, height = 41;
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
    this->window.create(sf::VideoMode(800, 600), "Dengeon");
    this->view = this->window.getDefaultView();

    // VSync 垂直同步
    window.setVerticalSyncEnabled(true);

    // FPS 限制
    window.setFramerateLimit(144);
}

void Game::update()
{
    sf::Event event;
    while ( this->window.pollEvent(event) )
    {
        if ( event.type == sf::Event::Closed )
            this->window.close();
        else if ( event.type == sf::Event::Resized )
        {
            // Update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            this->view.reset(visibleArea);
        }
        else if ( event.type == sf::Event::KeyPressed )
        {
            this->keyInput.press(event.key.code);
        }
        else if ( event.type == sf::Event::KeyReleased )
        {
            this->keyInput.release(event.key.code);
        }
    }

    // Update dt
    this->dt = clock.restart();

    // Clear
    this->window.clear();

    KeyInput *keyInputPtr = &this->keyInput;

    /**
     * Logic
     */
    this->world.logic(keyInputPtr, this->dt);
    this->player.logic(keyInputPtr, this->dt);
    this->camera.logic(keyInputPtr, this->dt);

    /**
     * Render
     */
    this->world.render(this->window);
    this->player.render(this->window);
    this->camera.render(this->window);

    // Update camera focus on player
    this->camera.focus(&this->player);

    // Set view as camera position
    this->camera.updateView(this->view);

    // Set View
    this->window.setView(view);
    // Display
    this->window.display();
}

void Game::run()
{
    while ( window.isOpen() )
        this->update();
}