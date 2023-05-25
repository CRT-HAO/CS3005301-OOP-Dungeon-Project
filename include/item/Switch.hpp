/**
 *  File: Switch.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/26 01:48:30
 *  Description: Switch Class
 */

#pragma once

#include "IItem.hpp"
#include "Position.hpp"

#include <sstream>

//************************************************************
// Switch Class
//************************************************************
class Switch : public IItem
{
private:
    bool _on;
    static const char OFF_ICON = '-';
    static const char ON_ICON = '^';

public:
    Switch() : IItem(TItem::kSwitch, OFF_ICON), _on(false) {}

    Switch(int x, int y) : IItem(TItem::kSwitch, OFF_ICON, x, y), _on(false) {}

    Switch(const Switch &ref) : IItem(TItem::kSwitch, OFF_ICON) { *this = ref; }

    virtual std::string getInfo() const override;

    virtual void update(Hero &hero) override;

    inline int getOn() const { return this->_on; }

    inline void setOn(bool on) { this->_on = on; }
};
