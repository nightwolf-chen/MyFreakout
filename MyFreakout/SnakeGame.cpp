#include "SnakeGame.h"
#include "SnakeSprite.h"
#include "blackbox.h"
#include <iostream>

SnakeSprite snake ;

int SnakeGame::Game_Init(void *parms)
{
	std::cout<<"Game snake is initializing...\n" ;
	return 0;
}
int SnakeGame::Game_Shutdown(void *parms)
{
	//std::cout<<"Game snake is shutdown!\n";
	
	snake.~SnakeSprite();

	return 0;
}
int SnakeGame::Game_Main(void *parms, HWND main_window_handle)
{
	snake.move();
	snake.draw();
	snake.addBlock();
	return 0;
}