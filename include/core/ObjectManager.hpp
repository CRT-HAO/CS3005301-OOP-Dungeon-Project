/**
 *  File: ObjectManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:21:55
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 00:21:13
 *  Description: Object Manager
 */

#pragma once

#include "Object.hpp"

#include <vector>

namespace Dungeon
{

    class ObjectManager : public Object
    {
    private:
        std::vector<Object *> objects;

    public:
        ObjectManager();

    public:
        void clear();
        void addObject(Object *);
        std::vector<Object *> getObjects();

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}