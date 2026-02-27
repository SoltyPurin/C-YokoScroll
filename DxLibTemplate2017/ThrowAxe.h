#pragma once
#include "Vector2.h"
#include "Rect.h"
class Axe
{
public:
	Axe();
	~Axe();
	void Update();
	void DrawAxe();
	void SetInfo(const Vector2& playerPos, bool isRight);	
	void Gravity();
	Vector2 GetPos();
	Rect GetColRect() const { return _axeCollision; }
private:
	int _axeHandle;
	float _axeVerticalY ;
	Vector2 _axePosition;
	Vector2 _move;
	Rect _axeCollision;
};

