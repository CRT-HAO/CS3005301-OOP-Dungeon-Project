/**
 *  File: View.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:01:41
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/04 20:22:02
 *  Description: View
 */

#pragma once

#include "../lib/json.hpp"
#include "PositionFloat.hpp"

#include <string>

using Json = nlohmann::json;

namespace Dungeon
{

    class View
    {
    public:
        Json data;

    public:
        View()
        {
            this->data["background"]["color"] = "#000000";
            this->clear();
        }

    public:
        inline void clear()
        {
            this->data["objects"] = Json::array();
        }

        inline void setBackgroundColor(const std::string &color)
        {
            this->data["background"]["color"] = color;
        }

        inline void addObject(const PositionFloat &pos, const Json &data)
        {
            Json tmp = {
                {
                    "position",
                    {
                        {
                            "x",
                            pos.x,
                        },
                        {
                            "y",
                            pos.y,
                        },
                    },
                }};
            tmp.update(data);
            this->data["objects"].push_back(tmp);
        };
    };
}