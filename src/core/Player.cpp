/**
 *  File: Player.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:43:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:09:47
 *  Description: Player Class
 */

#include "core/Player.hpp"

#include "SFML/System/Vector2.hpp"
#include "core/Entity.hpp"
#include "core/File.hpp"

#include <cmath>

using namespace Dungeon;

Player::Player(World *world) : world(world)
{
    this->weapon = new Weapon(world, this);
}

Player::Player(World *world, const sf::Vector2f &pos) : world(world)
{
    sprite.setPosition(pos);
    this->weapon = new Weapon(world, this);
}

Player::~Player()
{
    // delete this->weapon;
}

void Player::setWorld(World *world)
{
    this->world = world;
    if ( this->weapon != nullptr )
        this->weapon->setWorld(world);
}

bool Player::checkCollision(const sf::Vector2f &newPos)
{
    sf::Vector2f delta = newPos - this->getPos();
    sf::FloatRect hitbox = this->getHitBox();
    hitbox.left += delta.x;
    hitbox.top += delta.y;
    for ( Room *room : this->world->getRooms() )
    {
        if ( room->intersects(hitbox) )
            return true;
    }

    return false;
}

void Player::updateHitbox()
{
    float littleSpace = 10;
    sf::FloatRect hitbox = sprite.getGlobalBounds();
    hitbox.left += littleSpace / 2;
    hitbox.top += littleSpace / 2;
    hitbox.width -= littleSpace;
    hitbox.height -= littleSpace;
    this->setHitBox(hitbox);
}

void Player::updateAnimation(sf::Time &dt)
{
    if ( this->state == PlayerState::Idle )
    {
        if ( this->dirX == PlayerDirection::Left )
            this->animationManager.play("Idle_Left", dt);
        else
            this->animationManager.play("Idle_Right", dt);
    }
    else if ( this->state == PlayerState::Moving )
    {
        if ( this->dirX == PlayerDirection::Left )
            this->animationManager.play("Moving_Left", dt);
        else
            this->animationManager.play("Moving_Right", dt);
    }
}

void Player::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/spritesheet_player.png")
            .string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setScale(this->size / spriteSize, this->size / spriteSize);

    // 設置碰撞區域
    this->updateHitbox();

    // 動畫
    this->animationManager.addAnimation("Idle_Left", 0, 0, 0, 0, 0, spriteSize,
                                        spriteSize);
    this->animationManager.addAnimation("Idle_Right", 0, 4, 0, 4, 0, spriteSize,
                                        spriteSize);
    this->animationManager.addAnimation("Moving_Left", 0.08, 0, 0, 3, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Moving_Right", 0.08, 4, 0, 7, 0,
                                        spriteSize, spriteSize);

    // 武器
    this->weapon->init();
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
            this->dir = PlayerDirection::Up;
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
            this->dir = PlayerDirection::Down;
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
            this->dirX = PlayerDirection::Left;
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
            this->dirX = PlayerDirection::Right;
            this->dir = PlayerDirection::Right;
        }
    }

    // 更新碰撞區域
    this->updateHitbox();

    this->updateAnimation(dt);

    this->weapon->logic(keyInput, dt);

    std::cout << "HP=" << this->getHP() << std::endl;
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);

    this->weapon->render(window);

    // Debug: Draw hitbox
    // sf::RectangleShape rectangle;
    // rectangle.setPosition(this->getHitBox().left, this->getHitBox().top);
    // rectangle.setSize(
    //     sf::Vector2f(this->getHitBox().width, this->getHitBox().height));
    // rectangle.setFillColor(sf::Color::Color::Yellow);
    // window.draw(rectangle);
}

Json Player::toJson() const
{
    Json j;
    j["hp"] = this->hp;
    j["max_hp"] = this->maxHP;
    j["size"] = this->size;
    j["dirX"] = static_cast<int>(this->dirX);
    j["dir"] = static_cast<int>(this->dir);
    if ( this->weapon )
        j["weapon"] = this->weapon->toJson();
    j.update(Entity::toJson());
    return j;
}

void Player::fromJson(const Json &json)
{
    this->hp = json["hp"].get<float>();
    this->maxHP = json["max_hp"].get<float>();
    this->size = json["size"].get<size_t>();
    this->dirX = static_cast<PlayerDirection>(json["dirX"].get<int>());
    this->dir = static_cast<PlayerDirection>(json["dir"].get<int>());
    if ( json.contains("weapon") )
        this->weapon->fromJson(json["weapon"]);
    Entity::fromJson(json);
}
