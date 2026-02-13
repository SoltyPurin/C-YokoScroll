#pragma once
#include "Vector2.h"
#include "Rect.h"
class Stage;
class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	void DrawObstacle();
	void Update();
	Vector2 ReturnPos();
	float ReturnScale();
private:
	Stage* _stagePointer;
	Rect _collisionRect;

};

