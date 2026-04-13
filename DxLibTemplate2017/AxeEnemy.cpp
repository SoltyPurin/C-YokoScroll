#include "AxeEnemy.h"
#include "Enemy.h"
#include <DxLib.h>
#include "ShareClass.h"
#include "ThrowAxe.h"
#include "Player.h"
#include "Stage.h"


AxeEnemy::AxeEnemy(Stage* stage, float x, float y) : Enemy(stage, x, y) {
	_imageHandle = LoadGraph("Image/AxeEnemy.png");
	_scale = 99;
	ResetPosition();
}

AxeEnemy::~AxeEnemy() {
	DeleteGraph(_imageHandle);
}

void AxeEnemy::Update() {
	Gravity(ShareClass::KoteiValue);
	_currentPos.y -= _verticalY * _oneMinuteMovePixel * ShareClass::KoteiValue;
	float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;

	//_collisionRect.SetCenter(colX  ,colY , _scale, _scale);
	_collisionRect.SetCenter(colX + _scale, colY + _scale, _scale, _scale);

}


Axe* AxeEnemy::CreateAxe() {
	_currentThrowingTime += ShareClass::KoteiValue;
	if (_currentThrowingTime >=_nextThrowTime) {
		_currentThrowingTime = 0;
		Axe* axe = new Axe();
		float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
		float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
		Vector2 colVec = Vector2(colX + _scale, colY + _scale);
		axe->SetInfo(colVec, IsPlayerRight());
		return axe;
	}
	return nullptr;
}

bool AxeEnemy::IsPlayerRight() {
	bool isRight = false;
	float playerPos = _playerInfo->GetPos().x;
	float curX = _currentPos.x;
	//プレイヤーが左右どちらにいるかを判断
	if (curX - playerPos <=0) {//右にいると判断
		isRight = true;
	}

	return isRight;
}
