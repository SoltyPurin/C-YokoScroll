#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Stage.h"
class Rect;

class Character
{
public:
	Character();
	~Character();
	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual void TakeDamage();
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	virtual void CheckHitMap(Rect& chipRect);
	Rect ReturnRect();
	Rect GetColRect() const { return _collisionRect; }
	virtual void ResetPosition();
protected:
	int _imageHandle;
	void Gravity();
	float _verticalY;
	Stage* _stagePointer;
	Vector2 _pos;
	Vector2 _draw;
	Rect _collisionRect;
	float _scale = 99;
	float _gravity = 0.1f;
	float _initX = 320;
	float _initY = 600;
};


