#include "DxLib.h"
#include "ThrowAxe.h"

namespace
{
	constexpr float AXE_SPEED = 7.0f; // à⁄ìÆë¨ìx
	constexpr float AXE_VERTICAL = 15.5f; //êÇíºÇ…îÚÇŒÇ∑óÕ
	constexpr float GRAVITY = 0.5f;
}
float _axeScale = 80;

Axe::Axe():
_axePosition({0,0}),
_move({AXE_SPEED,0})
{
	_axeHandle = LoadGraph("Image/Axe.png");
}

Axe::~Axe() {
	DeleteGraph(_axeHandle);
}

void Axe::Update() {
	_axePosition += _move;
	_axePosition.y -= _axeVerticalY;
	Gravity();
	DrawAxe();
}
void Axe::SetInfo(const Vector2& playerPos, bool isRight) {
	_axePosition = playerPos;
	if (isRight) {
		_move.x = AXE_SPEED;
	}
	else {
		_move.x = -AXE_SPEED;
	}
	_axeVerticalY = AXE_VERTICAL;
}

void Axe::DrawAxe() {
	float plusPosx = _axePosition.x + _axeScale;
	float plusPosy = _axePosition.y + _axeScale;
	DrawExtendGraph(_axePosition.x, _axePosition.y, plusPosx, plusPosy, _axeHandle, TRUE);
}

void Axe::Gravity() {
	_axeVerticalY -= GRAVITY;
}

Vector2 Axe::GetPos() {
	return _axePosition;
}
