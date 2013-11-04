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
	MoveDown
}MoveDirection;

class SnakeSprite
{
public:
	SnakeSprite(int screenWidth,int screenHight);
	~SnakeSprite();
	bool move();
	void draw();
	void addBlock();
	void drawBlock(SnakeBlock *block);
	void setCurrentDirection(MoveDirection dir);
private:
	SnakeBlock *blocks;
	SnakeBlock *tailBlock;
	int blockCount;
	MoveDirection currentDir;

	int screenWidth;
	int screenHight;
	int speed;

};

