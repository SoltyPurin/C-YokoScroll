#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Weapons.h"

class ThrowKnife : public Weapons
{
public:
	ThrowKnife();
	//~ThrowKnife();
	virtual void Update() override;
	virtual void SetInfo(const Vector2& playerPos, bool isRight) override;
};

