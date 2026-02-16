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
	}
    Gravity();
	_pos.y -= _verticalY;
	_pos.x += _move.x;
	_collisionRect.SetCenter(_drawX + _playerScale * 0.5f, _drawY + _playerScale * 0.5f, _playerScale, _playerScale);
	DrawPlayer();
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

void Player::CheckHitMap(Rect& chipRect)
{
    // 当たり矩形
    _collisionRect.SetCenter(_pos.x, _pos.y, _playerScale - 1, _playerScale - 1);

    // まずは当たってるか
    if (!_stagePointer->IsCollision(_collisionRect, chipRect))
    {
        _isGround = false;
        return;
    }

    // めり込み量（左右・上下）
    float overlapL = _collisionRect.GetRight() - chipRect.GetLeft();   // 左へ押す量
    float overlapR = chipRect.GetRight() - _collisionRect.GetLeft(); // 右へ押す量
    float overlapT = _collisionRect.GetBottom() - chipRect.GetTop();    // 上へ押す量
    float overlapB = chipRect.GetBottom() - _collisionRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (_collisionRect.GetLeft() + _collisionRect.GetRight()) * 0.5f;
    float rcy = (_collisionRect.GetTop() + _collisionRect.GetBottom()) * 0.5f;
    float ccx = (chipRect.GetLeft() + chipRect.GetRight()) * 0.5f;
    float ccy = (chipRect.GetTop() + chipRect.GetBottom()) * 0.5f;

    // 重要：小さい軸だけ解決（壁に当たったのに縦へ押し戻す…を防ぐ）
    if (pushX < pushY)
    {
        // 横解決
        if (rcx < ccx)
            _pos.x -= pushX; // チップの左側にいる → 左へ
        else
            _pos.x += pushX; // チップの右側にいる → 右へ

        _move.x = 0.0f;
        // 横衝突だけでは地面判定は変えない（降りられない原因になりやすい）
    }
    else
    {
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _pos.y -= pushY;
            _verticalY = 0.0f;
            _isGround = true;
        }
        else
        {
            // 下から頭ぶつけ
            _pos.y += pushY;
            _verticalY = 0.0f;  
            _isGround = false;
        }
    }
}

Rect Player::ReturnRect() {
	return _collisionRect;
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
	jump.JumpProtocol(*this);
	_isGround = false;
}