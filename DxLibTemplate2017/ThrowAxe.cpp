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
	_axeCollision.SetCenter(_axePosition.x, _axePosition.y, _axeScale, _axeScale);
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
	float drawX = _axePosition.x - _axeScale * 0.5f;
	float drawY = _axePosition.y- _axeScale * 0.5f;

	float plusPosx = drawX + _axeScale;
	float plusPosy = drawY + _axeScale;
	DrawExtendGraph(drawX,drawY, plusPosx, plusPosy, _axeHandle, TRUE);
#ifdef _DEBUG
	// ìñÇΩÇËîªíËÇï\é¶
	_axeCollision.Draw(0x00ff00, false);
#endif

}

void Axe::Gravity() {
	_axeVerticalY -= GRAVITY;
}

Vector2 Axe::GetPos() {
	return _axePosition;
}
