/**
 * @ Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 * @ Create Time: 2023-02-21 19:52:33
 * @ Modified by: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 * @ Modified time: 2023-02-24 01:31:07
 * @ Description: Use clock to count time (And output) for following input tasks
 */

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

const clock_t PERIOD_MS = 1000;

int main(int argc, char **argv)
{
    clock_t startT, endT; // Variable to store the start of the gameloop
    startT = clock();
    endT = clock();
    clock_t globalStartT = startT;

    // Start the game loop
    for ( size_t i = 0; i < 15; i++ )
    {
        // Do something...

        // Check point
        // Record the end time
        endT = clock();

        clock_t ms = (endT - startT) / CLOCKS_PER_SEC * 1000;
        // If the loop time does not reach period
        if ( ms < PERIOD_MS )
            // Sleep until time reaches period
            this_thread::sleep_for(chrono::milliseconds(PERIOD_MS - ms));

        // Output loop time
        double currentSeconds = (clock() - globalStartT) / CLOCKS_PER_SEC;
        cout << "Total time " << i << " at " << fixed << currentSeconds << endl;

        // Record the start time
        startT = clock();
    }
}
