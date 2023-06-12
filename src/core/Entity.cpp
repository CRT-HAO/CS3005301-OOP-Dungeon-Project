/**
 *  File: Entity.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:05:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 07:08:54
 *  Description: Entity Class
 */

#include "core/Entity.hpp"
#include "SFML/System/Vector2.hpp"

using namespace Dungeon;

bool Entity::intersects(const sf::FloatRect &frect)
{
    return this->hitbox.intersects(frect);
}

Json Entity::toJson() const
{
    Json j;
    j["position"] = {
        {"x", this->getPos().x},
        {"y", this->getPos().y},
    };
    return j;
}

void Entity::fromJson(const Json &json)
{
    this->sprite.setPosition(sf::Vector2f(json["position"]["x"].get<float>(),
                                          json["position"]["y"].get<float>()));
}