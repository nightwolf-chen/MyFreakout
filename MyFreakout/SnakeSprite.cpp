/**********************************************************************************************//**
 * @file	SnakeSprite.cpp
 *
 * @brief	Implements the snake sprite class.
 **************************************************************************************************/

#include <windows.h>
#include <iostream>
#include "SnakeSprite.h"
#include "blackbox.h"
#include <cstdlib>

/**********************************************************************************************//**
 * @brief	֡��.
 **************************************************************************************************/
static const int fps = 30;

/**********************************************************************************************//**
 * @brief	ÿ�����ƶ��ĵ�Ԫ��.
 **************************************************************************************************/
static const int unitsPerSecond=30;

/**********************************************************************************************//**
 * @brief	The dir[ 5][2] �ֱ��ӦMoveDirection�������ƶ���ʽ
 **************************************************************************************************/
static int dir[5][2] = {{-1,0},{1,0},{0,-1},{0,1},{0,0}};

/**********************************************************************************************//**
 * @brief	��������.
 **************************************************************************************************/
static int count = 0;

int BlockWidth = 10;

/**********************************************************************************************//**
 * @fn	bool interseted(int x1,int y1,int x2,int y2)
 *
 * @brief	���þ��ε��������ж��Ƿ��ཻ��
 * @author	Exitingchen
 * @date	2013/11/6
 *
 * @param	x1	The first x value.
 * @param	y1	The first y value.
 * @param	x2	The second x value.
 * @param	y2	The second y value.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/
bool interseted(int x1,int y1,int x2,int y2)
{
	int x11 = x1 + BlockWidth;
	int y11 = y1 + BlockWidth;
	int x22 = x2 + BlockWidth;
	int y22 = y2 + BlockWidth;

	int centerDifX = abs(x11+x1-x22-x2);
	int centerDifY = abs(y11+y1-y22-y2);

	if(centerDifX < 2*BlockWidth && centerDifY < 2*BlockWidth){
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

	int startX = w/BlockWidth/2*BlockWidth;
	int startY = h/BlockWidth/2*BlockWidth;

	SnakeBlock *lastBlock;
	SnakeBlock *newBlock;

	for(int i = 0 ; i < blockCount;i++){

		newBlock = new SnakeBlock;
		newBlock->x = startX + i*BlockWidth;
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

	int tx = this->blocks->x + xIncrement*BlockWidth;
	int ty = this->blocks->y + yIncrement*BlockWidth;

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
	
	/*�������β�ڵ�ŵ�����ǰ���ظ����ã����������������ģ���ߵ����߷�ʽ*/
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

	//�����ߵ�ǰ���ƶ�������������Ҫ����block��λ��
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


	Draw_Rectangle(x,y,x+BlockWidth,y+BlockWidth,0);
}

void SnakeSprite::setCurrentDirection(MoveDirection dir)
{
	this->currentDir = dir;
}

bool SnakeSprite::detectConflictWithBlock(SnakeBlock *block)
{
	int &x = block->x;
	int &y = block->y;

	return interseted(x,y,this->blocks->x,this->blocks->y);
}