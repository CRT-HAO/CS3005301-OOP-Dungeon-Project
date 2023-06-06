/**
 *  File: ObjectsManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:21:55
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 15:36:35
 *  Description: Objects Manager
 */

#pragma once

#include "Object.hpp"

#include <vector>

namespace Dungeon
{

    class ObjectsManager : public Object
    {
    private:
        std::vector<Object *> objects;

    public:
        ObjectsManager();

    public:
        void clear();
        void addObject(Object *);

    public:
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}