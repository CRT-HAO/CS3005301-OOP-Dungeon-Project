/**
 *  File: Block.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 07:04:12
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 10:32:08
 *  Description: Block Class
 */

#include "core/block/Block.hpp"
#include "core/Entity.hpp"

using namespace Dungeon;

Json Block::toJson() const
{
    Json j;
    j["solid"] = this->solid;
    j["size"] = this->size;
    j["visible"] = this->visible;
    j.update(Entity::toJson());
    return j;
}

void Block::fromJson(const Json &json)
{
    this->solid = json["solid"].get<bool>();
    this->size = json["size"].get<size_t>();
    this->visible = json["visible"].get<bool>();
    Entity::fromJson(json);
}