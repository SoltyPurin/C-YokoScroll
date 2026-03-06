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
private:
	float _enemyScale = 99;
	float _enInitX = 320;
	float _enInitY = 0;
	float _enVerticalY = 0;
	float _enGravity = 0.1f;
};

