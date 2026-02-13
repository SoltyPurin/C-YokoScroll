#include "Player.h"
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
#include "Jump.h"
float _initX = 320;
float _initY = 600;
float _playerScale = 99;
float _verticalY = 0;
float _gravity = 0.1f;
int _playerGraph = 0;
float _groundY = 900;
float _drawX;
float _drawY;
bool _isGround = false;

Vector2 _pos;
Player _player;

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
	_move.x = moveValue;
}

void Player::Update() {
	if (!_isGround) {
		Gravity();
	}
	_pos.y -= _verticalY;
	_pos.x += _move.x;
	_collisionRect.SetCenter(_drawX + _playerScale * 0.5f, _drawY + _playerScale * 0.5f, _playerScale, _playerScale);
	DrawPlayer();
	CheckHitMap(_collisionRect);
}
void Player::DrawPlayer() {
	_drawX = _pos.x - _stagePointer->GetScrollX() - _playerScale * 0.5f;
	_drawY = _pos.y - _stagePointer->GetScrollY() - _playerScale * 0.5f;
	DrawExtendGraph(_drawX, _drawY, _drawX + _playerScale, _drawY + _playerScale, _playerGraph, TRUE);
	//DrawGraph(_currentX, _currentY, _playerGraph, TRUE);
#ifdef _DEBUG
// 当たり判定を表示
	_collisionRect.Draw(0x0000ff, false);
#endif
}

void Player::CheckHitMap(Rect chipRect)
{
	// 横から当たったかチェックする
	_pos.x += _move.x;
	_collisionRect.SetCenter(_pos.x, _pos.y, _playerScale-1, _playerScale-1);

	if (_stagePointer->IsCollision(_collisionRect, chipRect))
	{
		if (_move.x > 0.0f)
		{
			_pos.x = chipRect.GetLeft() - _playerScale * 0.5f;
		}
		else if (_move.x < 0.0f)
		{
			_pos.x = chipRect.GetRight() + _playerScale * 0.5f;
		}
		_move.x = 0.0f;
	}

	// 縦から当たったかチェックする
	//_pos.y += _verticalY;
	_collisionRect.SetCenter(_pos.x, _pos.y, _playerScale-1, _playerScale-1);

	if (_stagePointer->IsCollision(_collisionRect, chipRect))
	{
		if (_verticalY < 0.0f)
		{
			_pos.y = chipRect.GetTop() - _playerScale * 0.5f;
			_verticalY = 0.0f;
			_isGround = true;
		}
		else
		{
			_pos.y = chipRect.GetBottom() + _playerScale * 0.5f;
			_isGround = false;
			Gravity();
		}
	}
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

void Player::JumpProtocol(Jump& jump) {
	if (!_isGround) {
		return;
	}
	jump.JumpProtocol(_player);
}