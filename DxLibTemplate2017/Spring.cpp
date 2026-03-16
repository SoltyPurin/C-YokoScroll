#include "Spring.h"
#include "Stage.h"
#include "Vector2.h"
#include "Rect.h"
#include "DxLib.h"

Spring::Spring(Stage* stagePointer):
_isSpringActive(false),
_stagePointer(stagePointer){
	_springDeActiveHandle = LoadGraph("Image/SpringDeActive.png");
	_springActiveHandle = LoadGraph("Image/SpringActive.png");
	_viewSpringHandle = _springDeActiveHandle;
}

Spring::~Spring() {
	DeleteGraph(_springDeActiveHandle);
	DeleteGraph(_springActiveHandle);
	DeleteGraph(_viewSpringHandle);
}

void Spring::Update() {
	int currentTime = GetNowCount();
	_deltaTime = (currentTime - _prevTime) / 1000.0f;
	_prevTime = currentTime;

	if (_isSpringActive) {
		_currentActiveTime += _deltaTime;
	}

	if (_currentActiveTime >= _springActiveTime) {
		_currentActiveTime = 0;
		_isSpringActive = false;
		_viewSpringHandle = _springDeActiveHandle;
	}

	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	_collisionRect.SetCenter(colX + _scale * 1, colY + _scale * 1, _scale, _scale);
}
void Spring::DrawSpring(float scrrolX, float scrrolY) {
	int drawX = static_cast<int>(_currentPos.x - scrrolX);
	int drawY = static_cast<int>(_currentPos.y - scrrolY);
	int sizeX = drawX + _scale;
	int sizeY = drawY + _scale;
	DrawExtendGraph(drawX, drawY, sizeX, sizeY, _viewSpringHandle, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif
}
void Spring::SetPosition(float x, float y) {
	_currentPos.x = x;
	_currentPos.y = y;
}

void Spring::ActiveSpring() {
	_isSpringActive = true;
	_viewSpringHandle = _springActiveHandle;
}

