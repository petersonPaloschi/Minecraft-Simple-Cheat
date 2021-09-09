#include <iostream>
#include <Windows.h>
#include <thread> 
#include <chrono>

#include "click.hpp"

std::unique_ptr<c_clicker> clicker = std::make_unique<c_clicker>();

void c_clicker::click()
{
    for (;;)
    {
        if (GetAsyncKeyState(VK_XBUTTON1))
        {
            // 9 a 14 cps
            std::this_thread::sleep_for(std::chrono::milliseconds(18));
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        #ifndef DEBUG
        std::cout << "clicker on" << std::endl;
        #endif
    }

}


