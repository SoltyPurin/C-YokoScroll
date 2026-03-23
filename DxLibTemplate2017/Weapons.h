#pragma once
#include "Vector2.h"
#include "Rect.h"

class Weapons
{
public:
	Weapons();
	~Weapons();
	virtual void Update();
	virtual void DrawWeapon();
	virtual void SetInfo(const Vector2& playerPos, bool isRight);
	Vector2 GetPos();
	Rect GetColRect() const { return _weaponCollision; }

protected:
	int _weaponHandle;
	float _weaponScale = 80;
	bool _isRight = true;
	Vector2 _weaponPosition;
	Rect _weaponCollision;
	Vector2 _move;
	//1秒あたりなんピクセル進むか
	float _oneMinuteMovePixel = 100.0f;

};

