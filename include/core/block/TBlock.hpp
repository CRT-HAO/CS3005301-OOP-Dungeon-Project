/**
 *  File: TBlock.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:21:46
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/29 23:28:37
 *  Description: Block type definition
 */

#pragma once

namespace Dungeon
{

    enum class TBlock
    {
        kUndefined, // 未定義
        kGround,    // 地板
        kWall,      // 牆壁
    };

}