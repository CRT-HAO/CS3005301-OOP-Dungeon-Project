/**
 *  File: main.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/23 09:17:14
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023-04-23 17:56:43
 *  Description: 基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，
 *               到T上可以增加經驗ESC是離開畫面。同時更新圖版上的資訊。
 */

#include <conio.h>  // _getch() <= to read input without enter "ENTER" key
#include <math.h>   // pow() and sqrt()

#include <algorithm>  // for max and min function
#include <ctime>      // for time loop function
#include <iostream>

#include "Position.h"
#include "Trigger.h"

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard(int rowN, int colN);
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position &loc);

// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position &pos2);
