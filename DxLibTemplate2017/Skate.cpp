#include "Precompile.h"
#include "Skate.h"
#include "Stage.h"

Skate::Skate(Stage* stage, float x, float y):
_stagePointer(stage),
_currentPos(x,y),
_initPos(x,y),
_scale(99){
	_skateBoardHandle = LoadGraph("Image/Player/SkateBoard.png");
}

Skate::~Skate() {
	DeleteGraph(_skateBoardHandle);
}

void Skate::Update() {
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;

	//_collisionRect.SetCenter(colX  ,colY , _scale, _scale);
	_collisionRect.SetCenter(colX + _scale, colY + _scale, _scale, _scale);

}

void Skate::DrawSkateBoard(float scrollX,float scrollY) {
	int drawX = static_cast<int>(_currentPos.x - scrollX);
	int drawY = static_cast<int>(_currentPos.y - scrollY);
	int sizeX = drawX + _scale;
	int sizeY = drawY + _scale;

	DrawExtendGraph(drawX, drawY, sizeX, sizeY, _skateBoardHandle, TRUE);

#ifdef _DEBUG
	//// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif

}



