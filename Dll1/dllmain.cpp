#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4838 4309 )
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <thread> 
#include <chrono>
#include <string>

#include "click.hpp"
#include "reach.hpp"
#include "recraft.hpp"
#include "exit.hpp"
#include "sound.hpp"

void main_func()
{

	PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY);

	c_reacher f_reach;
	c_clicker f_click;
	c_recrafting f_recraft;
	c_exit f_exit;

	std::thread t_reacher(&c_reacher::reach, &f_reach);
	std::thread t_clicker(&c_clicker::click, &f_click);
	std::thread t_recraft(&c_recrafting::recraft, &f_recraft);
	std::thread t_exit(&c_exit::sair, &f_exit);

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	t_clicker.join();
	t_reacher.join();
	t_recraft.join();
	t_exit.join();

}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{


		DisableThreadLibraryCalls(hModule);

		#ifndef DEBUG
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CONOUT$", "w", stdout);
		#endif

		CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(main_func), hModule, 0, nullptr);
	}

	return TRUE;
}

