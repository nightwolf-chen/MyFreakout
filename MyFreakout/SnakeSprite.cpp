#include <windows.h>
#include <iostream>
#include "SnakeSprite.h"
#include "blackbox.h"
#include <cstdlib>

static const int fps = 30;
static const int unitsPerSecond=30;
static int dir[5][2] = {{-1,0},{1,0},{0,-1},{0,1},{0,0}};
static int count = 0;
int BlockWitdh = 10;

//利用矩形的中心来判断是否相交
bool interseted(int x1,int y1,int x2,int y2)
{
	int x11 = x1 + BlockWitdh;
	int y11 = y1 + BlockWitdh;
	int x22 = x2 + BlockWitdh;
	int y22 = y2 + BlockWitdh;

	int centerDifX = abs(x11+x1-x22-x2);
	int centerDifY = abs(y11+y1-y22-y2);

	if(centerDifX < 2*BlockWitdh && centerDifY < 2*BlockWitdh){
		return true;
	}
	return false;
}

SnakeSprite::SnakeSprite(int w,int h)
{
	screenWidth = w;
	screenHight = h;

	currentDir = MoveStay;
	
	blockCount = 4;
	this->speed = 5;

	int startX = w/BlockWitdh/2*BlockWitdh;
	int startY = h/BlockWitdh/2*BlockWitdh;

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
	if(currentDir == MoveStay){
		return false;
	}

	if(count-- > 0){
		return false;
	}else{
		count = fps / unitsPerSecond;
	}

	int xIncrement = dir[currentDir][0];
	int yIncrement = dir[currentDir][1];

	int tx = this->blocks->x + xIncrement*BlockWitdh;
	int ty = this->blocks->y + yIncrement*BlockWitdh;

	if(!(tx >= 0 && tx < this->screenWidth && ty >= 0 && ty < screenHight)){
		return false;
	}

	SnakeBlock *snakeP = this->blocks;

	while(snakeP != NULL){
	
		if(interseted(tx,ty,snakeP->x,snakeP->y)){
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

void SnakeSprite::addBlock(SnakeBlock block)
{
	//OutputDebugStringA("snake add");
	SnakeBlock *newBlock = new SnakeBlock;
	newBlock->x = block.x;
	newBlock->y = block.y;

	//根据蛇当前的移动方向来修正将要加入block的位置
	if (currentDir == MoveDown || currentDir == MoveUp)
	{
		newBlock->x = this->blocks->x;
	}
	else if(currentDir == MoveLeft || currentDir == MoveRight)
	{
		newBlock->y = this->blocks->y;
	}

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

	/*if(x == this->blocks->x && y == this->blocks->y){
		return true;
	}
		return false;*/
	return interseted(x,y,this->blocks->x,this->blocks->y);
}