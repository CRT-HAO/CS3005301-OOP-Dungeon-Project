/**
 *  File: Heal.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:28:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 15:34:11
 *  Description: Heal Block Class
 */

#include "core/block/Heal.hpp"
#include "core/File.hpp"
#include "core/Player.hpp"

using namespace Dungeon;

Heal::Heal(Player *player, float healHP) : player(player), healHP(healHP) {}

Heal::Heal(Player *player, const sf::Vector2f &pos, float healHP)
    : player(player), healHP(healHP)
{
    this->setPos(pos);
}

void Heal::init()
{
    int spriteSize = 16;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/heal_16x16.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(
        sf::IntRect(0, spriteSize, spriteSize, spriteSize));
    sprite.setScale(this->getSize() / spriteSize, this->getSize() / spriteSize);
    this->setSolid(false);

    this->animationManager.addAnimation("Rotating", 0.07, 0, 0, 5, 0,
                                        spriteSize, spriteSize);
}

void Heal::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( !this->isVisible() )
        return;

    this->animationManager.play("Rotating", dt);

    // 判斷玩家是否在可以操作方塊的範圍
    sf::FloatRect approachArea = this->sprite.getGlobalBounds();

    if ( approachArea.contains(this->player->getCenter()) )
    {
        this->player->heal(this->healHP);
        this->setVisible(false);
    }
}

void Heal::render(sf::RenderWindow &window)
{
    if ( !this->isVisible() )
        return;

    window.draw(this->sprite);
}

Json Heal::toJson() const
{
    Json j;
    j["type"] = "Heal";
    j["heal_hp"] = this->healHP;
    j.update(Block::toJson());
    return j;
}

void Heal::fromJson(const Json &json)
{
    this->healHP = json["heal_hp"].get<float>();
    Block::fromJson(json);
}