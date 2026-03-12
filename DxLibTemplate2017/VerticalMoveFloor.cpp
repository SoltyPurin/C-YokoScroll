#include "VerticalMoveFloor.h"
#include "DxLib.h"
VerticalMoveFloor::VerticalMoveFloor(Stage* stage):
	_stagePointer(stage)
{
	_floorHandle = LoadGraph("Image/moveFloor.png");
}

VerticalMoveFloor::~VerticalMoveFloor() {
	DeleteGraph(_floorHandle);
}

void VerticalMoveFloor::Update() {
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	_collisionRect.SetCenter(colX + _scale * 1, colY + _scale * 1, _scale, _scale);
}

void VerticalMoveFloor::DrawFloor(float scrolX,float scrolY) {
	int drawX = static_cast<int>(_currentPos.x - scrolX);
	int drawY = static_cast<int>(_currentPos.y - scrolY);
	DrawGraph(drawX, drawY, _floorHandle, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif

}

void VerticalMoveFloor::SetPosition(float x, float y) {
	_currentPos.x = x;
	_currentPos.y = y;
}
