#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "Character.h"

class Rect;
class Enemy
{
public:
	Enemy(Stage* stage,float x,float y);
	~Enemy();
	void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	void Update();
	void Draw(float scrollX, float scrollY);
	void CheckHitMap(Rect& chipRect);
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }
	void ResetPosition();
	void Gravity(float deltaTime);

private:
	int _imageHandle;
	int _scale = 99;
	float _prevTime;
	float _deltaTime;
	float _gravity = 10.5f;
	float _verticalY;
	float _oneMinuteMovePixel = 100.0f;
	Stage* _stagePointer;
	Vector2 _currentPos;
	Vector2 _initPos;
	Rect _collisionRect;
};

