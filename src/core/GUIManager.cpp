/**
 *  File: GUIManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:41:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 09:37:27
 *  Description: GUI Manager Class
 */

#include "core/GUIManager.hpp"
#include "core/KeyInput.hpp"

using namespace Dungeon;

GUIManager::GUIManager() {}

void GUIManager::addGUI(GUI *gui) { this->gui.insert(gui); }

void GUIManager::removeGUI(GUI *gui) { this->gui.erase(gui); }

void GUIManager::clear() { this->gui.clear(); }

void GUIManager::init()
{
    for ( const auto &g : this->gui )
        g->init();
}

void GUIManager::logic(KeyInput *keyInput, sf::Time &dt, sf::View &view)
{
    for ( auto &g : this->gui )
        g->logic(keyInput, dt, view);
}

void GUIManager::render(sf::RenderWindow &window)
{
    for ( auto &g : this->gui )
        g->render(window);
}