#include <windows.h>
#include <iostream>
#include "SnakeSprite.h"
#include "blackbox.h"

static int dir[5][2] = {{-1,0},{1,0},{0,-1},{0,1},{0,0}};
static int BlockWitdh = 5;

SnakeSprite::SnakeSprite(int w,int h)
{
	screenWidth = w;
	screenHight = h;

	currentDir = MoveStay;
	
	blockCount = 4;
	this->speed = 5;

	int startX = w/2;
	int startY = h/2;

	SnakeBlock *lastBlock;
	SnakeBlock *newBlock;

	for(int i = 0 ; i < blockCount;i++){

		newBlock = new SnakeBlock;
		newBlock->x = startX + i*BlockWitdh;
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

	int tx = this->blocks->x + xIncrement*speed;
	int ty = this->blocks->y + yIncrement*speed;

	if(!(tx >= 0 && tx < this->screenWidth && ty >= 0 && ty < screenHight)){
		return false;
	}

	SnakeBlock *snakeP = this->blocks;

	while(snakeP != NULL){
	
		if(tx == snakeP->x && ty == snakeP->y){
			return false;
		}

		snakeP = snakeP->next;
	}
	
	/*将链表的尾节点放到链表前段重复利用，利用链表的特性来模拟蛇的行走方式*/
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

	int blocksDrawed = 0 ;
	while(snakeP != NULL){
		this->drawBlock(snakeP);
		snakeP = snakeP->next;
		blocksDrawed++;
	}
	/*char debugstr[50];
	sprintf(debugstr,"blocksdrawed:%d\n",blocksDrawed);
	OutputDebugStringA(debugstr);*/
}

void SnakeSprite::addBlock(SnakeBlock *newBlock)
{
	//OutputDebugStringA("snake add");
	newBlock->next = this->blocks;
	newBlock->pre = NULL;
	
	this->blocks->pre = newBlock;
	this->blocks = newBlock;
}

void SnakeSprite::drawBlock(SnakeBlock *block)
{
	int &x = block->x;
	int &y = block->y;

	Draw_Rectangle(x,y,x+BlockWitdh,y+BlockWitdh,0);
}

void SnakeSprite::setCurrentDirection(MoveDirection dir)
{
	this->currentDir = dir;
}

bool SnakeSprite::detectConflictWithBlock(SnakeBlock *block)
{
	int &x = block->x;
	int &y = block->y;

	if(x == this->blocks->x && y == this->blocks->y){
		return true;
	}
		return false;
}