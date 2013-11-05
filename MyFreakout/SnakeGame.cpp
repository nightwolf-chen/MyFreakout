#include "SnakeGame.h"
#include "SnakeSprite.h"
#include "blackbox.h"
#include <iostream>

SnakeSprite snake(SCREEN_WIDTH, SCREEN_HEIGHT);
bool forInit = true;
SnakeBlock foodBlock;
long score = 0;
int scoreUnit = 100;

//Game main helpers.
SnakeBlock generateFoodBlock();
bool confictDetection();
void checkForUserInput();
void drawFrame();
void gameLogic();
void drawScore();
void drawAdditionalInfo(char *str);

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
		snake.move();
	}else{
		score+=scoreUnit;
	}

	snake.draw();
	snake.drawBlock(&foodBlock);
	drawScore();
	//drawAdditionalInfo("My First Windows Game!");

    DD_Flip();
    // sync to 33ish fps
    Wait_Clock(30);

	return 0;
}

//Game main helpers implements.
SnakeBlock generateFoodBlock()
{
	int foodX = rand()%(SCREEN_WIDTH - BlockWitdh);
	int foodY = rand()%(SCREEN_HEIGHT - BlockWitdh);
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
void drawScore()
{
	char buffer[30];
	sprintf(buffer,"不死贪吃蛇(1.0 nirvawolf) 得分：%d",score);
	Draw_Text_GDI(buffer, 8,SCREEN_HEIGHT-30, 127);
}
void drawAdditionalInfo(char *str)
{
	Draw_Text_GDI(str, (SCREEN_WIDTH-200) / 2,SCREEN_HEIGHT/2, 127);
}
