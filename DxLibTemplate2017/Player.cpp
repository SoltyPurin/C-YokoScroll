#include "Player.h"
#include <DxLib.h>
#include "Vector2.h"

float _initX = 320;
float _initY = 379;
float _scaleX = 99;
float _scaleY = 99;
float _startY = 379;
float _verticalY = 0;
float _gravity = 0.5f;
int _playerGraph = 0;

Vector2 _pos;

Player::Player() {
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
	if (_pos.y <= _startY) {
		_pos.y -= _verticalY;
	}
	else {
		_pos.y = _startY;
		_verticalY = 0;
	}

}
void Player::DrawPlayer() {
	DrawExtendGraph(_pos.x, _pos.y, _pos.x + _scaleX, _pos.y + _scaleY, _playerGraph, TRUE);
	//DrawGraph(_currentX, _currentY, _playerGraph, TRUE);
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