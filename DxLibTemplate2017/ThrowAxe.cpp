#include "DxLib.h"
#include "ThrowAxe.h"

namespace
{
	constexpr float AXE_SPEED = 10.0f; // ˆÚ“®‘¬“x
}
float _axeScale = 80;

ThrowAxe::ThrowAxe():
_axePosition({0,0}),
_move({AXE_SPEED,0})
{
	_axeHandle = LoadGraph("Image/Axe.png");
}

ThrowAxe::~ThrowAxe() {
	DeleteGraph(_axeHandle);
}

void ThrowAxe::Update() {
	_axePosition += _move;
	DrawAxe();
}
void ThrowAxe::SetInfo(const Vector2& playerPos, bool isRight) {
	_axePosition = playerPos;
	if (isRight) {
		_move.x = AXE_SPEED;
	}
	else {
		_move.x = -AXE_SPEED;
	}
}

void ThrowAxe::DrawAxe() {
	float plusPosx = _axePosition.x + _axeScale;
	float plusPosy = _axePosition.y + _axeScale;
	DrawExtendGraph(_axePosition.x, _axePosition.y, plusPosx, plusPosy, _axeHandle, TRUE);
}
