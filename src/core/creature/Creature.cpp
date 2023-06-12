/**
 *  File: Creature.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:57:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 07:09:55
 *  Description: Creature Class
 */

#include "core/creature/Creature.hpp"
#include "core/Entity.hpp"
#include "core/creature/ai_engine/AICreatureEngine.hpp"

using namespace Dungeon;

Creature::Creature(float hp) : aiEngine(nullptr), hp(hp)
{
    this->setZIndex(100);
}

Creature::Creature(World *world, Player *followPlayer, float hp) : hp(hp)
{
    this->setZIndex(100);
    this->aiEngine = new AICreatureEngine(world, this, followPlayer);
}

Creature::Creature(AICreatureEngine *aiEngine, float hp)
    : aiEngine(aiEngine), hp(hp)
{
    this->setZIndex(100);
}

void Creature::damage(float damage)
{
    this->hp -= std::min(damage, this->hp);
    this->underAttack = true;
}

void Creature::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->aiEngine != nullptr )
    {
        this->aiEngine->updatePosition(dt);
        this->aiEngine->updateAttack(dt, 5);
    }

    // 如果遭受攻擊
    if ( this->underAttack )
    {
        this->damageTime += dt;

        // 過1秒後解除遭受攻擊
        if ( this->damageTime.asSeconds() > 1 )
            this->underAttack = false;
    }

    this->setHitBox(this->sprite.getGlobalBounds());
}

void Creature::render(sf::RenderWindow &window) { window.draw(this->sprite); }

Json Creature::toJson() const
{
    Json j;
    j["hp"] = this->hp;
    if ( this->aiEngine )
        j["ai_engine"] = this->aiEngine->toJson();
    j.update(Entity::toJson());
    return j;
}

void Creature::fromJson(const Json &json)
{
    this->hp = json["hp"].get<float>();
    if ( json.contains("ai_engine") )
    {
        if ( this->aiEngine != nullptr )
            this->aiEngine->fromJson(json["ai_engine"]);
    }
    Entity::fromJson(json);
}