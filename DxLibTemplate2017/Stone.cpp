#include "Precompile.h"
#include "Stone.h"
#include "Stage.h"

Stone::Stone(int stoneHandle, Stage* stagePointer,Vector2 pos):
_stoneHandle(stoneHandle),
_stagePointer(stagePointer),
_currentPos(pos){
	_currentPos.y += 32.0f;
}

Stone::~Stone() {

}

void Stone::Update() {
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	_collisionRect.SetCenter(colX + _scale * 1, colY + _scale * 1, _scale * 0.5f, _scale);

}
void Stone::Draw(float scrrolX, float scrrolY) {
	int drawX = static_cast<int>(_currentPos.x - scrrolX);
	int drawY = static_cast<int>(_currentPos.y - scrrolY);
	int sizeX = drawX + _scale;
	int sizeY = drawY + _scale;
	DrawExtendGraph(drawX, drawY, sizeX, sizeY, _stoneHandle, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif

}