#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
class Stage;
class Rect;
class Goal
{
public:
	Goal(Stage* stagePointer,float x,float y);
	~Goal();
	void DrawGoal(float scrollX, float scrollY);
	void Update();
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }
private:
	int _goalHandle;
	int _scale = 99;

	Vector2 _currentPos;
	Rect _collisionRect;
	Stage* _stagePointer;


};

