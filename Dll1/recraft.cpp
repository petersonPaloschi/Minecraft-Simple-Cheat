#include <iostream>
#include <Windows.h>
#include <thread> 
#include <chrono>
#include <string>

#include "recraft.hpp"

std::unique_ptr<c_recrafting> recrafting = std::make_unique<c_recrafting>();






void LEFTDOWN()
{
    INPUT Input = { 0 };
    // Esquerdo clicka

    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));

    // Esquerdo Solta
    ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));


    std::this_thread::sleep_for(std::chrono::milliseconds(70));
}

void RIGHTDOWN()
{
    INPUT Input = { 0 };

    // Direito clicka
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &Input, sizeof(INPUT));


    // Direito Solta
    ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &Input, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::milliseconds(70));
}

void SHIFTDOWN()
{
    INPUT ip = { 0 };

    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0xA0; //shift
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));

}

void SHIFTUP()
{
    INPUT ip = { 0 };

    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0xA0; //shift
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

}


void  pos(int x, int y, int sleep, char type)
{

    const char types[3] = { 'i', 'o', 'p' }; //e = input //s = output //p = press

    SetCursorPos(x, y);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));

    if (type == types[0])
    {
        LEFTDOWN();
        RIGHTDOWN();
    }
    if (type == types[1])
    {
        LEFTDOWN();
    }
    if (type == types[2])
    {
        SHIFTDOWN();
        LEFTDOWN();
    }

}

void c_recrafting::recraft()
{
    for (;;)
    {
        if (GetAsyncKeyState(VK_XBUTTON2)) //mouse 
        {

            //Pote 
            pos(970, 570, 40, 'i');
            pos(995, 447, 40, 'o');

            //cogu vermelho
            pos(1025, 570, 40, 'i');
            pos(1050, 447, 40, 'o');

            //cogu marrom
            pos(1080, 570, 40, 'i');
            pos(1050, 399, 40, 'o');

            //saida recraft
            pos(1160, 421, 40, 'p');
            pos(995, 447, 40, 'p');
            pos(1050, 447, 40, 'p');
            pos(1050, 399, 40, 'p');

            SHIFTUP();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        #ifndef DEBUG
        std::cout << "Recraft on" << std::endl;
        #endif
    }
}




