/**
 *  File: View.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:01:41
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/05 23:14:20
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
            this->data["camera"] = {
                {"x", 0.0},
                {"y", 0.0},
            };
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

        inline void setCamera(const PositionFloat &pos)
        {
            this->data["camera"]["x"] = pos.x;
            this->data["camera"]["y"] = pos.y;
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