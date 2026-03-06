#include "Enemy.h"
#include <DxLib.h>
#include "Rect.h"



Enemy::Enemy() {
	_imageHandle = LoadGraph("Image/RedEnemy.png");
	_pos.x = _enInitX;
	_pos.y = _enInitY;
}

Enemy::~Enemy() {
	DeleteGraph(_imageHandle);
}

void Enemy::Update() {
	Gravity();
	_pos.y -= _verticalY;
	if (_pos.y >= _groundY) {
		_pos.y = _groundY;
		_verticalY = 0;
	}
	_collisionRect.SetCenter(_draw.x + _scale * 0.5f, _draw.y + _scale * 0.5f, _enemyScale, _enemyScale);
	Draw();
}

void Enemy::Draw() {
	_draw.x = _pos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	_draw.y = _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f;

	DrawExtendGraph(_draw.x, _draw.y, _draw.x + _enemyScale, _draw.y + _enemyScale, _imageHandle, true);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif

}
