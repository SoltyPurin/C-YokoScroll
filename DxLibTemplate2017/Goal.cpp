#include "Goal.h"
#include "DxLib.h"
Goal::Goal(Stage* stagePointer,float x, float y):
_stagePointer(stagePointer),
_currentPos(x,y){
	_goalHandle = LoadGraph("Image/Goal.png");
}

Goal::~Goal() {
	DeleteGraph(_goalHandle);
}

void Goal::Update() {
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	_collisionRect.SetCenter(colX + _scale * 1, colY + _scale * 1, _scale, _scale);

}

void Goal::DrawGoal(float scrollX,float scrollY) {
	int drawX = static_cast<int>(_currentPos.x - scrollX);
	int drawY = static_cast<int>(_currentPos.y - scrollY);
	int sizeX = drawX + _scale;
	int sizeY = drawY + _scale;
	DrawExtendGraph(drawX, drawY, sizeX, sizeY, _goalHandle, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif

}