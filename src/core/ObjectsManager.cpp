/**
 *  File: ObjectsManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:26:51
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/05 20:25:52
 *  Description: Objects Manager Class
 */

#include "core/ObjectsManager.hpp"

using namespace Dungeon;

ObjectsManager::ObjectsManager() {}

void ObjectsManager::addObject(Object *object)
{
    this->objects.push_back(object);
}

void ObjectsManager::logic(KeyInput *keyInput)
{
    for ( Object *ob : this->objects )
        ob->logic(keyInput);
}

void ObjectsManager::render(View *view)
{
    view->clear();
    for ( Object *ob : this->objects )
        ob->render(view);
}