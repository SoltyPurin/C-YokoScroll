#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
class Stage;
class Rect;
class VerticalMoveFloor
{
public:
	VerticalMoveFloor(Stage* stage);
	~VerticalMoveFloor();
	void Update();
	void DrawFloor(float scrrolX, float scrrolY);
	void SetPosition(float x, float y);
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }

private:
	int _floorHandle;

	int _scale = 99;
	//åªç›ÇÃç¿ïW
	Vector2 _currentPos;
	//ï`âÊÇ∑ÇÈç¿ïW
	Vector2 _currentDraw;

	Stage* _stagePointer;

	Rect _collisionRect;
};

