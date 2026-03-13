#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
class Stage;
class Rect;
class Spring
{
public:
	Spring(Stage* stagePointer);
	~Spring();
	void Update();
	void DrawSpring(float scrrolX, float scrrolY);
	void SetPosition(float x, float y);
	void ActiveSpring();
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }

private:
	int _springDeActiveHandle;

	int _springActiveHandle;

	int _viewSpringHandle;

	int _scale = 99;
	//Œ»İ‚ÌÀ•W
	Vector2 _currentPos;
	//•`‰æ‚·‚éÀ•W
	Vector2 _currentDraw;

	Stage* _stagePointer;

	Rect _collisionRect;

	//ŠÔ
	float _deltaTime = 0;
	//Å‰‚ÌŠÔ
	float _prevTime = 0;

	bool _isSpringActive;

	float _springActiveTime = 1.5f;

	float _currentActiveTime;

};

