/**
 *  File: Player.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:43:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 03:12:43
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
    sprite.setScale(this->size / spriteSize, this->size / spriteSize);

    // 設置碰撞區域
    this->setHitBox(sprite.getGlobalBounds());

    // 動畫
    this->animationManager.addAnimation("Idle_Left", 0,
                                        0, 0, 0, 0, spriteSize, spriteSize);
    this->animationManager.addAnimation("Idle_Right", 0,
                                        4, 0, 4, 0, spriteSize, spriteSize);
    this->animationManager.addAnimation("Moving_Left", 0.08,
                                        0, 0, 3, 0, spriteSize, spriteSize);
    this->animationManager.addAnimation("Moving_Right", 0.08,
                                        4, 0, 7, 0, spriteSize, spriteSize);
}

void Player::updateAnimation(sf::Time &dt)
{
    if ( this->state == PlayerState::Idle )
    {
        if ( this->dir == PlayerDirection::Left )
            this->animationManager.play("Idle_Left", dt);
        else
            this->animationManager.play("Idle_Right", dt);
    }
    else if ( this->state == PlayerState::Moving )
    {
        if ( this->dir == PlayerDirection::Left )
            this->animationManager.play("Moving_Left", dt);
        else
            this->animationManager.play("Moving_Right", dt);
    }
}

void Player::logic(KeyInput *keyInput, sf::Time &dt)
{
    this->state = PlayerState::Idle;

    double speed = 10 * GRID_SIZE * dt.asSeconds();
    if ( keyInput->isUp() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.y -= speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
        {
            this->sprite.setPosition(newPos);
            this->state = PlayerState::Moving;
        }
    }

    if ( keyInput->isDown() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.y += speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
        {
            this->sprite.setPosition(newPos);
            this->state = PlayerState::Moving;
        }
    }

    if ( keyInput->isLeft() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.x -= speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
        {
            this->sprite.setPosition(newPos);
            this->state = PlayerState::Moving;
            this->dir = PlayerDirection::Left;
        }
    }

    if ( keyInput->isRight() )
    {
        sf::Vector2f newPos = this->sprite.getPosition();
        newPos.x += speed;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
        {
            this->sprite.setPosition(newPos);
            this->state = PlayerState::Moving;
            this->dir = PlayerDirection::Right;
        }
    }

    this->updateAnimation(dt);
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}