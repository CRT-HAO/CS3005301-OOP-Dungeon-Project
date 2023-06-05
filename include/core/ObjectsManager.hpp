/**
 *  File: ObjectsManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:21:55
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/05 20:25:30
 *  Description: Objects Manager
 */

#pragma once

#include "Object.hpp"
#include "View.hpp"

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
        void addObject(Object *);

    public:
        virtual void logic(KeyInput *keyInput) override;
        virtual void render(View *view) override;
    };

}