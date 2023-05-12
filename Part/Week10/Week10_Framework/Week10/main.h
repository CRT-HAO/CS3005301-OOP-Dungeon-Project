/**
 *  File: main.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/11 00:50:58
 *  Description: 本輸入方向移動功能，w s a d 移動腳色上下左右，
                 空白改變腳色站立之地板字元，到T上可以增加經驗，
                 ESC是離開畫面。同時更新圖版上的資訊。
 */

#include "Position.h"
#include "Trigger.h"
#include <algorithm> // for max and min function
#include <conio.h>   // _getch() <= to read input without enter "ENTER" key
#include <ctime>     // for time loop function
#include <iostream>
#include <math.h> // pow() and sqrt()
// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position &loc);
// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，
// 利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position &pos2);
