#include "Player.h"
#include <DxLib.h>

int _currentX = 320;
int _currentY = 320;
int _startY = 320;
int _verticalY = 0;
int _gravity = 1;
int _playerGraph = 0;

void Player::Start() {
	_playerGraph = LoadGraph("Image/sample.png");
}
void Player::Move(int moveValue) {
	_currentX += moveValue;
}

void Player::Update() {
	if (_currentY <= _startY) {
		_currentY -= _verticalY;
	}
	else {
		_currentY = _startY;
		_verticalY = 0;
	}

}
void Player::DrawPlayer() {
	DrawGraph(_currentX, _currentY, _playerGraph, TRUE);
}

void Player::Gravity() {
	 _verticalY -= _gravity;
}
void Player::SetVY(int vy) {
	_verticalY = vy;
}
int Player::ReturnY() {
	return _currentY;
}

int Player::ReturnVY() {
	return _verticalY;
}