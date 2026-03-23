#include "Player.h"
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
#include "Jump.h"
#include "ThrowAxe.h"
#include "ThrowKnife.h"
#include "Pad.h"



Player::Player(float x,float y):Character(x,y)
{
    _weaponIndex = 0;
    _prevTime = GetNowCount();
    ResetPosition();
	_imageHandle = LoadGraph("Image/sample.png");
    _weaponCount = static_cast<int>(WeaponKinds::Max);
}
Player::~Player() {
	DeleteGraph(_imageHandle);
}
void Player::Move(float moveValue,bool isRight) {
	_move.x = moveValue;
    _isRight = isRight;
}

void Player::Update() {
    _deltaTime = 0.016f;
    //int currentTime = GetNowCount();
    //_deltaTime = (currentTime - _prevTime) / 1000.0f;
    //_prevTime = currentTime;
    Gravity(_deltaTime);
	_pos.y -= _verticalY * _oneMinuteMovePixel * _deltaTime;
	_pos.x += _move.x * _oneMinuteMovePixel * _deltaTime;
	_collisionRect.SetCenter(_draw.x + _scale * 0.5f, _draw.y + _scale * 0.5f, _scale, _scale);
	//Draw();
}
void Player::ChangeWeapon() {
    _weaponIndex++;
    if (_weaponIndex >= _weaponCount) {
        _weaponIndex = 0;
    }
}
void Player::Draw() {
	_draw.x = _pos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	_draw.y = _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
    if (_isRight) {
        DrawExtendGraph(_draw.x, _draw.y, _draw.x + _scale, _draw.y + _scale, _imageHandle, TRUE);
    }
    else {
        DrawExtendGraph(_draw.x + _scale, _draw.y, _draw.x, _draw.y + _scale, _imageHandle, TRUE);
    }
#ifdef _DEBUG
// 当たり判定を表示
	_collisionRect.Draw(0x0000ff, false);
#endif
}
int Player::ReturnCurrentWeaponIndex() {
    return _weaponIndex;
}
void Player::CheckHitMap(Rect& chipRect)
{
    // 当たり矩形
    _collisionRect.SetCenter(_pos.x, _pos.y, _scale - 1, _scale - 1);

    // まずは当たってるか
    if (!_stagePointer->IsCollision(_collisionRect, chipRect))
    {
        if (!_isGround) {
            _isGround = false;
        }
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

        //_move.x = 0.0f;
        // 横衝突だけでは地面判定は変えない（降りられない原因になりやすい）
    }
    else
    {
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _pos.y -= pushY;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
            }
            _isGround = true;
        }
        else
        {
            // 下から頭ぶつけ
            _pos.y += pushY;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
            }
            _isGround = false;
        }
    }

}
void Player::CheckObstacleHitMap(Rect& obstacleRect,bool isSpring) {
    // 当たり矩形
    //     _collisionRect.SetCenter(_pos.x, _pos.y, _scale - 1, _scale - 1);

    //_collisionRect.SetCenter(_pos.x, _pos.y, _scale , _scale);
    if (!_collisionRect.IsCollision(obstacleRect)) return;

    // めり込み量（左右・上下）
    float overlapL = _collisionRect.GetRight() - obstacleRect.GetLeft();   // 左へ押す量
    float overlapR = obstacleRect.GetRight() - _collisionRect.GetLeft(); // 右へ押す量
    float overlapT = _collisionRect.GetBottom() - obstacleRect.GetTop();    // 上へ押す量
    float overlapB = obstacleRect.GetBottom() - _collisionRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (_collisionRect.GetLeft() + _collisionRect.GetRight()) * 0.5f;
    float rcy = (_collisionRect.GetTop() + _collisionRect.GetBottom()) * 0.5f;
    float ccx = (obstacleRect.GetLeft() + obstacleRect.GetRight()) * 0.5f;
    float ccy = (obstacleRect.GetTop() + obstacleRect.GetBottom()) * 0.5f;

    // 重要：小さい軸だけ解決（壁に当たったのに縦へ押し戻す…を防ぐ）
    if (pushX < pushY)
    {
        // 横解決
        if (rcx < ccx)
            _pos.x -= pushX; // チップの左側にいる → 左へ
        else
            _pos.x += pushX; // チップの右側にいる → 右へ

    }
    else
    {
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _pos.y -= pushY;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
                _isGround = true;
            }
            if (isSpring) {
                _jumpAddres->SpringJumpProtocol(*this);
            }
        }
    }
}

ThrowKnife* Player::CreateKnife() {
    if (_weaponIndex != static_cast<int>(WeaponKinds::UseKnife)) {
        return nullptr;
    }
    if (Pad::IsTrigger(PAD_INPUT_3)) {
        ThrowKnife* knife = new ThrowKnife();
        knife->SetInfo(_draw, _isRight);
        return knife;
    }
    return nullptr;
}
Axe* Player::CreateAxe() {
    if (_weaponIndex != static_cast<int>(WeaponKinds::UseAxe)) {
        return nullptr;
    }
    if (Pad::IsTrigger(PAD_INPUT_3)) {
        Axe* axe = new Axe();
        axe->SetInfo(_draw, _isRight);
        return axe;
    }

    return nullptr;
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

void Player::JumpProtocol() {
	if (!_isGround) {
		return;
	}
    _jumpAddres->JumpProtocol(*this);
	_isGround = false;
}
void Player::ResetPosition() {
    _pos.x = _initX;
    _pos.y = _initY;
}