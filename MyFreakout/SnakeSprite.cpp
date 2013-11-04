#include "SnakeSprite.h"
#include <windows.h>

SnakeSprite::SnakeSprite(void)
{
}

SnakeSprite::~SnakeSprite(void)
{
	OutputDebugStringA("destroy snake");
}

bool SnakeSprite::move()
{
	OutputDebugStringA("snake moves");
	return true;
}

void SnakeSprite::draw()
{
	OutputDebugStringA("snake draws");
}

void SnakeSprite::addBlock()
{
	OutputDebugStringA("snake add");
}