#pragma once
#include "Vector2.h"
class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	void DrawObstacle();
	Vector2 ReturnPos();
	Vector2 ReturnScale();
};

