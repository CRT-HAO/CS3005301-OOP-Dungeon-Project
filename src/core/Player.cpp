/**
 *  File: Player.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:43:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 01:58:18
 *  Description: Player Class
 */

#include "core/Player.hpp"

#include "core/File.hpp"

#include <cmath>

using namespace Dungeon;

Player::Player(World *world) : world(world) {}

Player::Player(World *world, const sf::Vector2f &pos) : world(world)
{
    sprite.setPosition(pos);
}

bool Player::checkCollision(const sf::Vector2f &newPos)
{
    sf::FloatRect hitbox = this->getHitBox();
    hitbox.left = newPos.x;
    hitbox.top = newPos.y;
    for ( Room *room : this->world->getRooms() )
    {
        if ( room->intersects(hitbox) )
            return true;
    }

    return false;
}

void Player::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(fs::path(File::getResPath() / "images/spritesheet_player.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);

    // 設置碰撞區域
    this->setHitBox(sprite.getGlobalBounds());
}

void Player::logic(KeyInput *keyInput, sf::Time &dt)
{
    double speed = 10 * GRID_SIZE * dt.asSeconds();
    if ( keyInput->isUp() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.y -= speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->sprite.setPosition(newPos);
    }

    if ( keyInput->isDown() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.y += speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->sprite.setPosition(newPos);
    }

    if ( keyInput->isLeft() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.x -= speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->sprite.setPosition(newPos);
    }

    if ( keyInput->isRight() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.x += speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->sprite.setPosition(newPos);
    }
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}
