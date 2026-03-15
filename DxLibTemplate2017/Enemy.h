#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "Character.h"

class Rect;
class Enemy : public Character
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void Update()override;
	virtual void Draw()override;
	virtual void CheckHitMap(Rect& chipRect) override;
	void SetPosition(float x, float y);
private:
	float _enInitX = 220;
	float _enInitY = 0;
	float _enVerticalY = 0;
	float _enGravity = 0.1f;
	float _centerX;
	float _centerY;
};

