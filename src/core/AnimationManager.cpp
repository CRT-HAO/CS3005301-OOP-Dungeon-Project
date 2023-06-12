/**
 *  File: AnimationManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/07 02:35:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:08:28
 *  Description: Animation Manager
 */

#include "core/AnimationManager.hpp"

using namespace Dungeon;

AnimationManager::AnimationManager(sf::Sprite &sprite,
                                   sf::Texture &texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr)
{
}

AnimationManager::~AnimationManager()
{
    // for ( auto &i : this->animations )
    // {
    //     delete i.second;
    // }
}

const bool &AnimationManager::isDone(const std::string &key)
{
    return this->animations[key]->isDone();
}

void AnimationManager::addAnimation(const std::string &key,
                                    float animation_timer, int start_frame_x,
                                    int start_frame_y, int frames_x,
                                    int frames_y, int width, int height)
{
    this->animations[key] = new Animation(
        this->sprite, this->textureSheet, animation_timer, start_frame_x,
        start_frame_y, frames_x, frames_y, width, height);
}

const bool &AnimationManager::play(const std::string key, sf::Time &dt)
{
    if ( this->lastAnimation != this->animations[key] )
    {
        if ( this->lastAnimation == nullptr )
            this->lastAnimation = this->animations[key];
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }

    this->animations[key]->play(dt);

    return this->animations[key]->isDone();
}