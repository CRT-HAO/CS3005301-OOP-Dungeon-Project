/**
 *  File: Game->cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:36:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:44:12
 *  Description: Game Class
 */

#include "core/Game.hpp"
#include "core/GameSave.hpp"
#include "core/WorldGenerator.hpp"

#include <iostream>

using namespace Dungeon;

Game *Game::instance = nullptr;

Game::Game()
{
    this->world = new World(nullptr);
    this->player = new Player(nullptr);
    this->camera = new Camera();

    this->world->setPlayer(this->player);
    this->player->setWorld(this->world);
}

Game *Game::getInstance()
{
    if ( instance == nullptr )
        instance = new Game();

    return instance;
}

void Game::saveFile()
{
    std::cout << "Input save file name: ";
    std::string filename;
    std::cin >> filename;
    filename += ".json";
    GameSave save;
    save.fromInstance(this, this->gameData, this->level);
    if ( save.saveFile(filename) )
        std::cout << "Save file success!";
    else
        std::cout << "Save file failed!";
}

void Game::loadFile()
{
    std::cout << "Input load save file name: ";
    std::string filename;
    std::cin >> filename;
    filename += ".json";
    GameSave save;
    if ( !save.loadFile(filename) )
    {
        std::cout << "Load save file failed!";
        return;
    }

    this->gameData.loadJson(save.getGameDataJson());
    this->fromJson(save.getGameJson());
    this->level = save.getLevel();
    std::cout << "Load save file success!";
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

    // // 產生預設世界
    // WorldGenerator::genDefaultWorld(this->world, this->player, 15);

    this->gameData.loadFile();

    this->fromJson(this->gameData.getLevelData(this->level));

    // this->objectManager.addObject(this->world);

    // this->objectManager.addObject(this->player);
    // this->objectManager.addObject(this->camera);

    // this->playerGUI.setPlayer(this->player);

    this->guiManager.addGUI(&this->playerGUI);
    this->guiManager.addGUI(&this->gameGUI);

    // Init
    // this->objectManager.init();
    this->guiManager.init();
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
    this->guiManager.logic(&this->keyInput, this->dt, this->view);

    // Update creatures number
    this->gameGUI.setCurrentCreatureNum(
        this->world->getCreatureManager().getCreautresNum());

    /**
     * Render
     */
    this->objectManager.render(this->window);
    this->guiManager.render(this->window);

    // Update camera focus on player
    this->camera->focus(this->player);

    // Set view as camera position
    this->camera->updateView(this->view);

    // Set View
    this->window.setView(view);

    // Display
    this->window.display();

    if ( keyInput.isSaveFile() )
        this->saveFile();

    if ( keyInput.isLoadFile() )
        this->loadFile();

    if ( this->world->getCreatureManager().getCreautresNum() == 0 &&
         this->level < this->gameData.getLevelNum() - 1 )
    {
        this->level += 1;
        // this->world->clear();
        this->fromJson(this->gameData.getLevelData(this->level));
    }
}

void Game::run()
{
    this->init();
    std::cout << this->toJson().dump() << std::endl;
    while ( window.isOpen() )
        this->update();
}

Json Game::toJson() const
{
    Json j;
    j["player"] = this->player->toJson();
    j["world"] = this->world->toJson();
    j["camera"] = this->camera->toJson();
    return j;
}

void Game::fromJson(const Json &json)
{
    this->world = new World(nullptr);
    this->player = new Player(nullptr);
    this->camera = new Camera();

    this->world->setPlayer(this->player);
    this->player->setWorld(this->world);

    this->player->fromJson(json["player"]);
    this->camera->fromJson(json["camera"]);
    this->world->fromJson(json["world"]);

    this->objectManager.clear();

    this->objectManager.addObject(this->world);

    this->objectManager.addObject(this->player);
    this->objectManager.addObject(this->camera);

    this->playerGUI.setPlayer(this->player);

    this->objectManager.init();
}