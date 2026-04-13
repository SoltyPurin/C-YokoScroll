#include "VerticalMoveFloor.h"
#include "DxLib.h"
#include "ShareClass.h"
VerticalMoveFloor::VerticalMoveFloor(Stage* stage) :
	_stagePointer(stage),
	_upperFlagValue(-1)
{
	_floorHandle = LoadGraph("Image/moveFloor.png");
}

VerticalMoveFloor::~VerticalMoveFloor() {
	DeleteGraph(_floorHandle);
}

void VerticalMoveFloor::Update() {

	// 1. 更新前の座標を覚えておく
	float oldY = _currentPos.y;

	// 2. 本来の移動処理（サイン波や速度加算など）
	if (_currentPos.y < _upperLimit) {
		_currentPos.y = _upperLimit;
		_upperFlagValue = 1;
	}
	else if (_currentPos.y > _downerLimit) {
		_currentPos.y = _downerLimit;
		_upperFlagValue = -1;
	}

	_currentPos.y += _floorMoveSpeed * _oneMinuteMovePixel * ShareClass::KoteiValue * _upperFlagValue;
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	_collisionRect.SetCenter(colX + _scale * 1, colY + _scale * 1, _scale, _scale);
	// 3. 移動量（今の座標 - 1フレーム前の座標）を計算して保持しておく
	_moveDeltaY = _currentPos.y - oldY;
}

void VerticalMoveFloor::DrawFloor(float scrolX,float scrolY) {
	int drawX = static_cast<int>(_currentPos.x - scrolX);
	int drawY = static_cast<int>(_currentPos.y - scrolY);
	DrawGraph(drawX, drawY, _floorHandle, TRUE);
#ifdef _DEBUG
	// 当たり判定を表示
	_collisionRect.Draw(0x0000ff, false);
#endif

}

void VerticalMoveFloor::SetPosition(float x, float y) {
	_currentPos.x = x;
	_currentPos.y = y;
	_upperLimit = _currentPos.y - _moveRange;
	_downerLimit = _currentPos.y + _moveRange;

}
