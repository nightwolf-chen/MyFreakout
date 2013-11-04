#include "SnakeGame.h"
#include "blackbox.h"
#include <iostream>


int SnakeGame::Game_Init(void *parms)
{
	std::cout<<"Game snake is initializing...\n" ;
	
	return 0;
}
int SnakeGame::Game_Shutdown(void *parms)
{
	std::cout<<"Game snake is shutdown!\n";
	return 0;
}
int SnakeGame::Game_Main(void *parms, HWND main_window_handle)
{
	std::cout<<"Entering game snake main loop...\n";

	OutputDebugStringA("Entering game snake main loop...\n");

	return 0;
}