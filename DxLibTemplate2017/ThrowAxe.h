#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Weapons.h"
class Axe : public Weapons
{
public:
	Axe();
	//~Axe();
  	virtual void Update() override;
	void Gravity();
	virtual void SetInfo(const Vector2& playerPos, bool isRight) override;

private:
	float _axeVerticalY = 0;
};

