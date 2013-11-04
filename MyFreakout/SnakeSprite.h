#pragma once
class SnakeSprite
{
public:
	SnakeSprite(void);
	~SnakeSprite(void);
	bool move();
	void draw();
	void addBlock();
};

