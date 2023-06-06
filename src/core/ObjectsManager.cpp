/**
 *  File: ObjectsManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:26:51
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 17:00:20
 *  Description: Objects Manager Class
 */

#include "core/ObjectsManager.hpp"

using namespace Dungeon;

ObjectsManager::ObjectsManager() {}

void Dungeon::ObjectsManager::clear()
{
    this->objects.clear();
}

void ObjectsManager::addObject(Object *object)
{
    this->objects.push_back(object);
}

void ObjectsManager::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Object *ob : this->objects )
        ob->logic(keyInput, dt);
}

void ObjectsManager::render(sf::RenderWindow &window)
{
    for ( Object *ob : this->objects )
        ob->render(window);
}