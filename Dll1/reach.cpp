#include <iostream>
#include <Windows.h>
#include <thread> 
#include <chrono>
#include <vector>
#include <tchar.h>

#include "reach.hpp"

std::unique_ptr<c_reacher> reacher = std::make_unique<c_reacher>();

HANDLE pHandle = NULL;
DWORD pID = NULL;

std::vector < DWORD > adress45list;
std::vector < DWORD > reachlist;
std::vector < DWORD > reachlistdbl;
std::vector < DWORD > limitlist;

float valorReach = 4.5;

void c_reacher::reach()
{
    for (;;)
    {
        HWND mc_hWnd = FindWindow(_T("LWJGL"), nullptr);

        GetWindowThreadProcessId(mc_hWnd, &pID);

        pHandle = OpenProcess(THREAD_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pID);

        constexpr unsigned min = 0x10000; // Minimo 
        constexpr unsigned max = 0x06FFFFFF; // Maximo 

        char buffer[min];

        for (unsigned i = 0; i < max; i += min)
        {
            if (ReadProcessMemory(pHandle, (LPVOID)i, buffer, sizeof(buffer), nullptr))
            {
                for (int j = 0; j <= min - sizeof(double); ++j)
                {
                    double valor;

                    int endereco1 = i + j;
                    int endereco2 = i + j;
                    int endereco3 = i + j;
                    int endereco4 = i + j;

                    memcpy(&valor, buffer + j, sizeof(double));

                    if (i + j >= 0x02A0000C)
                    {
                        if (valor == 4.5)
                        {
                            for (int k = 0; k < 26; k++)
                            {
                                float checks;
                                endereco1 = endereco1 + 0x4;
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                                ReadProcessMemory(pHandle, (void*)endereco1, &checks, sizeof(checks), 0);

                                if (checks == 3.0)
                                {
                                    reachlist.push_back(endereco1);
                                    limitlist.push_back(i + j);
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            }
                            for (int k = 0; k < 16; k++)
                            {
                                float checks;
                                endereco2 = endereco2 - 0x4;
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                                ReadProcessMemory(pHandle, (void*)endereco2, &checks, sizeof(checks), 0);

                                if (checks == 3.0)
                                {
                                    reachlist.push_back(endereco2);
                                    limitlist.push_back(i + j);
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            }
                            for (int k = 0; k < 8; k++)
                            {
                                double checks;
                                endereco3 = endereco3 + 0x8;
                                ReadProcessMemory(pHandle, (void*)endereco3, &checks, sizeof(checks), 0);

                                if (checks == 3.0)
                                {
                                    reachlistdbl.push_back(endereco3);
                                    limitlist.push_back(i + j);
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            }
                            for (int k = 0; k < 8; k++)
                            {
                                double checks;
                                endereco4 = endereco4 - 0x8;
                                ReadProcessMemory(pHandle, (void*)endereco4, &checks, sizeof(checks), 0);

                                if (checks == 3.0)
                                {
                                    reachlistdbl.push_back(endereco4);
                                    limitlist.push_back(i + j);
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < reachlistdbl.size(); i++)
        {
            double value;
            ReadProcessMemory(pHandle, (LPVOID)(reachlistdbl.at(i)), &value, sizeof(value), NULL);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if (value <= 6.0)
            {
                if (value >= 3.0)
                {
                    if (value != valorReach)
                    {
                        WriteProcessMemory(pHandle, (void*)(reachlistdbl.at(i)), &valorReach, sizeof(double), 0);
                    }
                }

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        for (int i = 0; i < reachlist.size(); i++)
        {
            float value;
            ReadProcessMemory(pHandle, (LPVOID)(reachlist.at(i)), &value, sizeof(value), NULL);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if (value <= 6.0)
            {
                if (value >= 3.0)
                {
                    if (value != valorReach)
                    {
                        WriteProcessMemory(pHandle, (LPVOID)(reachlist.at(i)), &valorReach, sizeof(float), 0);
                    }
                }
            }
        }

        double valorReachlimit = valorReach + 1.5;

        for (int i = 0; i < limitlist.size(); i++)
        {
            double value;
            ReadProcessMemory(pHandle, (LPVOID)(limitlist.at(i)), &value, sizeof(value), NULL);

            if (value <= 7.5)
            {
                if (value >= 4.5)
                {
                    if (value != valorReachlimit)
                    {
                        WriteProcessMemory(pHandle, (LPVOID)(limitlist.at(i)), &valorReachlimit, sizeof(double), 0);
                    }
                }

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    #ifndef DEBUG
    std::cout << "Reach on" << std::endl;
    #endif


    }
}

