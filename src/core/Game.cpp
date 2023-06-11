/**
 *  File: Game->cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:36:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:29:18
 *  Description: Game Class
 */

#include "core/Game.hpp"
#include "core/WorldGenerator.hpp"

using namespace Dungeon;

Game *Game::instance = nullptr;

Game::Game() {}

Game *Game::getInstance()
{
    if ( instance == nullptr )
        instance = new Game();

    return instance;
}

void Game::init()
{
    this->window.create(sf::VideoMode(800, 600), "DaBian");
    this->view = this->window.getDefaultView();

    // VSync 垂直同步
    window.setVerticalSyncEnabled(true);

    // FPS 限制
    window.setFramerateLimit(144);

    /**
     * Initialize game data
     */

    // Set rand seed to time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    objectManager.clear();

    // 產生預設世界
    WorldGenerator::genDefaultWorld(&this->world, &this->player);

    objectManager.addObject(&world);

    objectManager.addObject(&player);
    objectManager.addObject(&camera);

    // Init
    objectManager.init();
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
            sf::FloatRect visibleArea(0, 0, event.size.width,
                                      event.size.height);
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
    this->objectManager.logic(&this->keyInput, this->dt);

    /**
     * Render
     */
    this->objectManager.render(this->window);

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
    this->init();
    while ( window.isOpen() )
        this->update();
}