#include <windows.h>
#include <iostream>
#include "SnakeSprite.h"
#include "blackbox.h"

static int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

SnakeSprite::SnakeSprite(int w,int h)
{
	screenWidth = w;
	screenHight = h;

	currentDir = MoveLeft;
	
	blockCount = 20;

	int startX = w/2;
	int startY = h/2;

	SnakeBlock *lastBlock;
	SnakeBlock *newBlock;

	for(int i = 0 ; i < blockCount;i++){

		newBlock = new SnakeBlock;
		newBlock->x = startX - i;
		newBlock->y = startY;

		if(i == 0){

			lastBlock = newBlock;
			this->blocks = newBlock;
			this->blocks->pre = NULL;

		}else{
			
			lastBlock->next = newBlock;
			newBlock->pre = lastBlock;
			lastBlock = newBlock;
			newBlock->next = NULL;
		}

	}

	this->tailBlock = newBlock;

}

SnakeSprite::~SnakeSprite()
{
	//OutputDebugStringA("destroy snake");
}

bool SnakeSprite::move()
{
	//OutputDebugStringA("snake moves");

	int xIncrement = dir[currentDir][0];
	int yIncrement = dir[currentDir][1];

	int tx = this->blocks->x + xIncrement;
	int ty = this->blocks->y + yIncrement;

	if(!(tx > 0 && tx < this->screenWidth && ty > 0 && ty < screenHight)){
		return false;
	}

	SnakeBlock *snakeP = this->blocks;

	while(snakeP != NULL){
	
		if(tx == snakeP->x && ty == snakeP->y){
			return false;
		}

		snakeP = snakeP->next;
	}
	
	//将链表的尾节点放到链表前段重复利用，利用链表的特性来模拟蛇的行走方式
	this->tailBlock->pre->next = NULL;

	this->tailBlock->next = this->blocks;
	this->tailBlock->x = tx;
	this->tailBlock->y = ty;

	this->blocks->pre = this->tailBlock;
	this->blocks = this->tailBlock;

	this->tailBlock = this->tailBlock->pre;
	this->tailBlock->next = NULL;

	return true;
}

void SnakeSprite::draw()
{
	SnakeBlock *snakeP = this->blocks;

	while(snakeP != NULL){
		
		/*int &x = snakeP->x;
		int &y = snakeP->y;

		Draw_Rectangle(x,y,x+5,y+5,0);*/

		this->drawBlock(snakeP);

		snakeP = snakeP->next;
	}

	//OutputDebugStringA("-----------------------\n");
}

void SnakeSprite::addBlock()
{
	//OutputDebugStringA("snake add");
}

void SnakeSprite::drawBlock(SnakeBlock *block)
{
	int &x = block->x;
	int &y = block->y;
	Draw_Rectangle(x,y,x+10,y+10,0);
}