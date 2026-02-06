#include "Player.h"
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"

float _initX = 320;
float _initY = 379;
float _scale = 99;
float _verticalY = 0;
float _gravity = 0.5f;
int _playerGraph = 0;
float _groundY = 900;
float _drawX;
float _drawY;

Vector2 _pos;

Player::Player():
_stagePointer(nullptr)
{
	_pos.x = _initX;
	_pos.y = _initY;
	_playerGraph = LoadGraph("Image/sample.png");
}
Player::~Player() {
	DeleteGraph(_playerGraph);
}
void Player::Move(float moveValue) {
	_pos.x += moveValue;
}

void Player::Update() {
	if (_pos.y <= _groundY) {
		_pos.y -= _verticalY;
	}
	else {
		_pos.y = _groundY;
		_verticalY = 0;
	}
	_collisionRect.SetCenter(_drawX + _scale * 0.5f, _drawY + _scale * 0.5f, _scale, _scale);

}
void Player::DrawPlayer() {
	_drawX = _pos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	_drawY = _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	DrawExtendGraph(_drawX, _drawY, _drawX + _scale, _drawY + _scale, _playerGraph, TRUE);
	//DrawGraph(_currentX, _currentY, _playerGraph, TRUE);
#ifdef _DEBUG
// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0x0000ff, false);
#endif
}

void Player::Gravity() {
	 _verticalY -= _gravity;
}
void Player::SetVY(float vy) {
	_verticalY = vy;
}
float Player::ReturnVY() {
	return _verticalY;
}

Vector2 Player::GetPos() {
	return _pos;
}