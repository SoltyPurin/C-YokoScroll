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
	void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	Rect GetColRect() const { return _collisionRect; }
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
	float _groundY = 900;
};


