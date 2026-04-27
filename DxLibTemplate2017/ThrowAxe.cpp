#include "Precompile.h"
#include "ThrowAxe.h"
#include "Weapons.h"
#include "ShareClass.h"

namespace
{
	constexpr float AXE_SPEED = 12.0f; // à⁄ìÆë¨ìx
	constexpr float AXE_VERTICAL = 15.5f; //êÇíºÇ…îÚÇŒÇ∑óÕ
	constexpr float GRAVITY = 1.0f;
}

Axe::Axe() : Weapons(){
	_move.x = AXE_SPEED;
	_weaponHandle = LoadGraph("Image/Axe.png");
}

void Axe::Update() {
	Weapons::Update();
	_weaponPosition += _move * _oneMinuteMovePixel * ShareClass::ConstValue;
	_weaponPosition.y -= _axeVerticalY * _oneMinuteMovePixel * ShareClass::ConstValue;
	Gravity();
}
void Axe::SetInfo(const Vector2& userPos, bool isRight) {
	_weaponPosition = userPos;
	if (isRight) {
		_move.x = AXE_SPEED;
	}
	else {
		_move.x = -AXE_SPEED;
	}
	_axeVerticalY = AXE_VERTICAL;
}

void Axe::Gravity() {
	_axeVerticalY -= GRAVITY * _oneMinuteMovePixel * ShareClass::ConstValue;
}
