#include "SnakeGame.h"
#include "SnakeSprite.h"
#include "blackbox.h"
#include <iostream>

SnakeSprite snake(SCREEN_WIDTH, SCREEN_HEIGHT);
bool forInit = true;
SnakeBlock foodBlock;

int SnakeGame::Game_Init(void *parms)
{
	std::cout<<"Game snake is initializing...\n" ;
	return 0;
}
int SnakeGame::Game_Shutdown(void *parms)
{
	snake.~SnakeSprite();
	return 0;
}


//Game main helpers
SnakeBlock generateFoodBlock();
bool confictDetection();
void checkForUserInput();
void drawFrame();
void gameLogic();

int SnakeGame::Game_Main(void *parms, HWND main_window_handle)
{
	//Init graphics stuff when first launched.
	if(forInit){
		DD_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
		forInit = false;
		foodBlock = generateFoodBlock();
	}

	//开始时钟，同时把返回值用作随机数种子。
	srand(Start_Clock());

	Draw_Rectangle(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1,200);
	
	checkForUserInput();
	
	if(!confictDetection()){
		gameLogic();
	}

	snake.draw();
	snake.drawBlock(&foodBlock);

    DD_Flip();

    // sync to 33ish fps
    Wait_Clock(30);

	return 0;
}

SnakeBlock generateFoodBlock()
{
	int foodX = rand()%SCREEN_WIDTH;
	int foodY = rand()%SCREEN_HEIGHT;
	SnakeBlock food;
	food.x = foodX;
	food.y = foodY;
	return food;
}

bool confictDetection()
{
	if (snake.detectConflictWithBlock(&foodBlock))
	{
		snake.addBlock(foodBlock);
		foodBlock = generateFoodBlock();
		return true;
	}
		return false;
}

void checkForUserInput()
{
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
}

void drawFrame()
{
	// clear drawing surface for the next frame of animation
	
	
	OutputDebugStringA("drawframe\n");
}

void gameLogic()
{
	snake.move();
}