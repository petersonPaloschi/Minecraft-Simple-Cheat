#include <iostream>
#include <Windows.h>
#include <thread> 
#include <chrono>
#include "exit.hpp"

std::unique_ptr<c_exit> exitt = std::make_unique<c_exit>();

void c_exit::sair()
{
	for (;;)
	{
		if (GetAsyncKeyState(0x73)) //f4
		{
			exit(0);
		}

		std::this_thread::sleep_for(std::chrono::seconds(5));

		#ifndef DEBUG
		std::cout << "Exit on" << std::endl;
		#endif
	}
}