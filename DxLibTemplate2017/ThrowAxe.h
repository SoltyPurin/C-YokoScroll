#pragma once
#include "Vector2.h"
class ThrowAxe
{
public:
	ThrowAxe();
	~ThrowAxe();
	void Update();
	void DrawAxe();
	void SetInfo(const Vector2& playerPos, bool isRight);	
private:
	int _axeHandle;
	Vector2 _axePosition;
	Vector2 _move;
};

