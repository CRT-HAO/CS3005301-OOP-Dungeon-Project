/**
 *  File: ObjectManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:26:51
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 00:21:31
 *  Description: Object Manager Class
 */

#include "core/ObjectManager.hpp"

using namespace Dungeon;

ObjectManager::ObjectManager() {}

void Dungeon::ObjectManager::clear()
{
    this->objects.clear();
}

void ObjectManager::addObject(Object *object)
{
    this->objects.push_back(object);
}

std::vector<Object *> ObjectManager::getObjects()
{
    return this->objects;
}

void ObjectManager::init()
{
    for ( Object *ob : this->objects )
        ob->init();
}

void ObjectManager::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Object *ob : this->objects )
        ob->logic(keyInput, dt);
}

void ObjectManager::render(sf::RenderWindow &window)
{
    for ( Object *ob : this->objects )
        ob->render(window);
}