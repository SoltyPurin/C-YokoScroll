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
	virtual void Update();
	void Draw(float scrollX, float scrollY);
	void CheckHitMap(Rect& chipRect);
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }
	void ResetPosition();
	void Gravity(float deltaTime);
	void FlagChange();

protected:
	int _imageHandle;
	int _scale = 99;
	int _colScale = 70;
	//ˆÚ“®•ûŒüA1‚Å¶A-1‚Å‰E
	int _moveFlag = 1;
	float _gravity = 10.5f;
	float _verticalY;
	float _oneMinuteMovePixel = 1.0f;
	float _moveRange;
	float _flagChangeXPos;
	Stage* _stagePointer;
	Vector2 _currentPos;
	Vector2 _initPos;
	Rect _collisionRect;
};

