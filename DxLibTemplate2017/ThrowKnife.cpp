#include "ThrowKnife.h"
#include "DxLib.h"
#include "Weapons.h" 
namespace
{
	constexpr float Knife_SPEED = 7.0f; // ˆÚ“®‘¬“x
}


ThrowKnife::ThrowKnife() : Weapons() {
	_move.x = Knife_SPEED;
	_weaponHandle = LoadGraph("Image/Knife.png");
}
void ThrowKnife::Update(){
	Weapons::Update();
	_weaponPosition += _move * _oneMinuteMovePixel * _deltaTime;
	_weaponCollision.SetCenter(_weaponPosition.x, _weaponPosition.y, _weaponScale, _weaponScale);
	DrawWeapon();
}

void ThrowKnife::SetInfo(const Vector2& playerPos, bool isRight) {
	_weaponPosition = playerPos;
	if (isRight) {
		_move.x = Knife_SPEED;
	}
	else {
		_move.x = -Knife_SPEED;
	}
	_isRight = isRight;
}
