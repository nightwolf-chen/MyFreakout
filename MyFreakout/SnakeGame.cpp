#include "SnakeGame.h"
#include "SnakeSprite.h"
#include "blackbox.h"
#include <iostream>

SnakeSprite snake = SnakeSprite();

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
	OutputDebugStringA("Entering game snake main loop...\n");
	return 0;
}