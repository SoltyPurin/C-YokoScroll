#include "DxLib.h"
#include "ThrowAxe.h"
#include "Weapons.h"

namespace
{
	constexpr float AXE_SPEED = 7.0f; // à⁄ìÆë¨ìx
	constexpr float AXE_VERTICAL = 15.5f; //êÇíºÇ…îÚÇŒÇ∑óÕ
	constexpr float GRAVITY = 0.5f;
}

Axe::Axe() : Weapons()
{
	_move.x = AXE_SPEED;
	_weaponHandle = LoadGraph("Image/Axe.png");
}

void Axe::Update() {
	Weapons::Update();
	_weaponPosition += _move * _oneMinuteMovePixel * _deltaTime;
	_weaponPosition.y -= _axeVerticalY * _oneMinuteMovePixel * _deltaTime;
	_weaponCollision.SetCenter(_weaponPosition.x, _weaponPosition.y, _weaponScale, _weaponScale);
	Gravity();
	DrawWeapon();
}
void Axe::SetInfo(const Vector2& playerPos, bool isRight) {
	_weaponPosition = playerPos;
	if (isRight) {
		_move.x = AXE_SPEED;
	}
	else {
		_move.x = -AXE_SPEED;
	}
	_axeVerticalY = AXE_VERTICAL;
}

void Axe::Gravity() {
	_axeVerticalY -= GRAVITY;
}
