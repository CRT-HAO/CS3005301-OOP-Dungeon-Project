/**
 *  File: Trigger.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/26 01:37:02
 *  Description: Trigger Class
 */

#pragma once

#include "IItem.hpp"
#include "Position.hpp"

#include <sstream>

//************************************************************
// Trigger Class
//************************************************************
class Trigger : public IItem
{
private:
    int _exp;

public:
    Trigger() : IItem(TItem::kTrigger, 'T'), _exp(10) {}

    Trigger(int x, int y) : IItem(TItem::kTrigger, 'T', x, y), _exp(10) {}

    Trigger(const Trigger &ref) : IItem(TItem::kTrigger, 'T') { *this = ref; }

    virtual std::string getInfo() const override;

    virtual void update(Hero &hero) override;

    inline int getExpAmount() const { return this->_exp; }
};
