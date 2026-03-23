#include "DxLib.h"
#include "ThrowAxe.h"
#include "Weapons.h"

namespace
{
	constexpr float AXE_SPEED = 6.0f; // à⁄ìÆë¨ìx
	constexpr float AXE_VERTICAL = 15.5f; //êÇíºÇ…îÚÇŒÇ∑óÕ
	constexpr float GRAVITY = 1.0f;
}

Axe::Axe() : Weapons(){
	_move.x = AXE_SPEED;
	_weaponHandle = LoadGraph("Image/Axe.png");
}

void Axe::Update() {
	Weapons::Update();
	_weaponPosition += _move * _oneMinuteMovePixel * _deltaTime;
	_weaponPosition.y -= _axeVerticalY * _oneMinuteMovePixel * _deltaTime;
	Gravity();
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
	_axeVerticalY -= GRAVITY * _oneMinuteMovePixel * _deltaTime;
}
