/**
 *  File: KeyInput.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 19:36:38
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 02:06:37
 *  Description: Key Input Class
 */

#pragma once

#include <map>

namespace Dungeon
{

    class KeyInput
    {
    private:
        std::map<char, bool> keys;

    public:
        KeyInput();

    public:
        void clear();

        inline void setKey(char key, bool value) { this->keys[key] = value; };
        inline void press(char key) { this->keys[key] = true; };
        inline void release(char key) { this->keys[key] = false; };
        inline bool pressed(char key) const { return this->keys.at(key); };

    public:
        inline bool isUp() const
        {
            return (this->keys.at('w') || this->keys.at('W'));
        }

        inline bool isDown() const
        {
            return (this->keys.at('s') || this->keys.at('S'));
        }

        inline bool isLeft() const
        {
            return (this->keys.at('a') || this->keys.at('A'));
        }

        inline bool isRight() const
        {
            return (this->keys.at('d') || this->keys.at('D'));
        }

    public:
        inline bool &operator[](char key) { return this->keys[key]; }
    };

}