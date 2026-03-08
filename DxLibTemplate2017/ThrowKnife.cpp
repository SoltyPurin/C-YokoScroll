#include "ThrowKnife.h"
#include "DxLib.h"
#include "Weapons.h" 
namespace
{
	constexpr float Knife_SPEED = 7.0f; // ˆÚ“®‘¬“x
}


ThrowKnife::ThrowKnife() {
	_move.x = Knife_SPEED;
	_weaponHandle = LoadGraph("Image/Axe.png");
}
ThrowKnife::~ThrowKnife() {
	DeleteGraph(_weaponHandle);
}
void ThrowKnife::Update(){
	_weaponPosition += _move;
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
}
