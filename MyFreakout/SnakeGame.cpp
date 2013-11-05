#include "SnakeGame.h"
#include "SnakeSprite.h"
#include "blackbox.h"
#include <iostream>

SnakeSprite snake(SCREEN_WIDTH, SCREEN_HEIGHT);
bool forInit = true;


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
	if(forInit){
	 // initialize everything here graphics
		DD_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
		forInit = false;
	}
	
	int foodX = rand()%SCREEN_WIDTH;
	int foodY = rand()%SCREEN_HEIGHT;
	SnakeBlock *food = new SnakeBlock;
	food->x = foodX;
	food->y = foodY;
	//Start_Clock();
	srand(Start_Clock());
    // clear drawing surface for the next frame of animation
    Draw_Rectangle(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1,200);

	if (KEY_DOWN(VK_RIGHT))
	{
		snake.setCurrentDirection(MoveRight);
	}
	else if(KEY_DOWN(VK_LEFT))
	{
		snake.setCurrentDirection(MoveLeft);
	}
	else if(KEY_DOWN(VK_UP))
	{
		snake.setCurrentDirection(MoveUp);
	}
	else if(KEY_DOWN(VK_DOWN))
	{
		snake.setCurrentDirection(MoveDown);
	}

	snake.move();
	snake.draw();
	snake.addBlock();

	snake.drawBlock(food);

    DD_Flip();

    // sync to 33ish fps
    Wait_Clock(30);
	return 0;
}