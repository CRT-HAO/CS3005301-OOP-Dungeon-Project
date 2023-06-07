/**
 *  File: Door.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:28:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 12:35:08
 *  Description: Door Block Class
 */

#include "core/block/Door.hpp"
#include "core/File.hpp"

using namespace Dungeon;

Door::Door(Player *player) : player(player) {}

Door::Door(Player *player, const sf::Vector2f &pos) : player(player)
{
    this->setPos(pos);
}

void Door::init()
{
    int spriteSize = 8;
    this->textureClosed = sf::IntRect(spriteSize * 2, spriteSize * 1,
                                      spriteSize, spriteSize);
    this->textureOpened = sf::IntRect(spriteSize * 3, spriteSize * 1,
                                      spriteSize, spriteSize);
    this->textureTest = sf::IntRect(0, spriteSize * 2,
                                    spriteSize, spriteSize);

    this->texture.loadFromFile(fs::path(File::getResPath() / "images/tilemap.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, spriteSize, spriteSize, spriteSize));
    sprite.setScale(this->getSize() / spriteSize, this->getSize() / spriteSize);

    this->setSolid(true);
}

void Door::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->isClosed() )
        this->sprite.setTextureRect(this->textureClosed);
    else
        this->sprite.setTextureRect(this->textureOpened);

    // 如果門關住則為實體
    this->setSolid(this->isClosed());

    // 判斷玩家是否在可以操作方塊的範圍
    sf::FloatRect approachArea = this->sprite.getGlobalBounds();
    approachArea.left -= this->getSize();
    approachArea.top -= this->getSize();
    approachArea.width *= 3;
    approachArea.height *= 3;

    if ( approachArea.contains(this->player->getCenter()) )
    {
        this->playerApproach = true;
        if ( this->isClosed() )
        {
            this->sprite.setTextureRect(this->textureTest);
            // 按下Enter開門
            if ( keyInput->isEnter() )
                this->setClosed(false);
        }
    }
    else
        this->playerApproach = false;
}

void Door::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}