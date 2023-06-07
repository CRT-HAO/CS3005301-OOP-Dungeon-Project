/**
 *  File: KeyInput.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 19:36:38
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 11:27:24
 *  Description: Key Input Class
 */

#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <map>

namespace Dungeon
{

    class KeyInput
    {
    private:
        std::map<sf::Keyboard::Key, bool> keys;

    public:
        KeyInput();

    public:
        void clear();

        inline void setKey(sf::Keyboard::Key key, bool value) { this->keys[key] = value; };
        inline void press(sf::Keyboard::Key key) { this->keys[key] = true; };
        inline void release(sf::Keyboard::Key key) { this->keys[key] = false; };
        inline bool pressed(sf::Keyboard::Key key) const { return this->keys.at(key); };

    public:
        inline bool isUp() const
        {
            return this->keys.at(sf::Keyboard::Key::W);
        }

        inline bool isDown() const
        {
            return this->keys.at(sf::Keyboard::Key::S);
        }

        inline bool isLeft() const
        {
            return this->keys.at(sf::Keyboard::Key::A);
        }

        inline bool isRight() const
        {
            return this->keys.at(sf::Keyboard::Key::D);
        }

        inline bool isEnter() const
        {
            return this->keys.at(sf::Keyboard::Key::Enter);
        }

    public:
        inline bool &operator[](sf::Keyboard::Key key) { return this->keys[key]; }
    };

}