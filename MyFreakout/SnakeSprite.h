#pragma once

typedef struct SnakeBlock{
	int x;
	int y;
	SnakeBlock *next;
	SnakeBlock *pre;
}SnakeBlock;

typedef enum MoveDirection{
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	MoveStay
}MoveDirection;

class SnakeSprite
{
public:
	SnakeSprite(int screenWidth,int screenHight);
	~SnakeSprite();
	bool move();
	void draw();
	void addBlock(SnakeBlock *newBlock);
	void drawBlock(SnakeBlock *block);
	void setCurrentDirection(MoveDirection dir);
	bool detectConflictWithBlock(SnakeBlock *block);
private:
	SnakeBlock *blocks;
	SnakeBlock *tailBlock;
	int blockCount;
	MoveDirection currentDir;
	int screenWidth;
	int screenHight;
	int speed;
};

