#include "Player.h"
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
#include "Jump.h"
#include "ThrowAxe.h"
#include "ThrowKnife.h"
#include "Pad.h"
#include "ShareClass.h"
#include "SoundPlayer.h"
#include "VerticalMoveFloor.h"
 


Player::Player(float x, float y, PlayerImages images) :Character(x, y),
_idleHandle(images._idle),
_moveOneHandle(images._move1),
_moveTwoHandle(images._move2),
_jumpHandle(images._jump),
_throwHandle(images._throw),
_blowAwayHandle(images._blowAway),
_initBlowAwayPower(_blowAwayPower)
{
    _weaponIndex = 0;
    ResetPosition();
    _useHandle = _idleHandle;
    _weaponCount = static_cast<int>(WeaponKinds::Max);
}
Player::~Player() {
}
void Player::Move(float moveValue,bool isRight) {
    if (_isBlowing) {
        return;
    }
	_move.x = moveValue;
    _isRight = isRight;
    if (moveValue == 0 && _isGround && !_isThrowing) {
        _currentState = PlayerState::Idle;
        _isMoveing = false;
    }
    else {
        if (_isGround && !_isThrowing) {
            _currentState = PlayerState::Move;
            _isMoveing = true;
        }
    }

}

void Player::Update() {
    Gravity(ShareClass::KoteiValue);
    if (_isBlowing) {
        BlowAway();
        _blowTime += ShareClass::KoteiValue;
    }
    else {
        _pos.x += _move.x * _oneMinuteMovePixel * ShareClass::KoteiValue;
    }
	_pos.y -= _verticalY * _oneMinuteMovePixel * ShareClass::KoteiValue;
	_collisionRect.SetCenter(_draw.x + _scale * 0.5f, _draw.y + _scale * 0.5f, _scale*0.5f, _scale);
    if (_isThrowing) {
        _currentThrowingTime += ShareClass::KoteiValue;
        _currentState = PlayerState::Throw;
    }
    if (_currentThrowingTime >= _throwStateTime) {
        _currentThrowingTime = 0;
        _isThrowing = false;
    }
}
void Player::ChangeWeapon() {
    _weaponIndex++;
    if (_weaponIndex >= _weaponCount) {
        _weaponIndex = 0;
    }
}
void Player::Draw() {
    ChangeHandle();
	_draw.x = _pos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	_draw.y = _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
    if (_isRight) {
        DrawExtendGraph(_draw.x, _draw.y, _draw.x + _scale, _draw.y + _scale, _useHandle, TRUE);
    }
    else {
        DrawExtendGraph(_draw.x + _scale, _draw.y, _draw.x, _draw.y + _scale, _useHandle, TRUE);
    }
#ifdef _DEBUG
// 当たり判定を表示
	_collisionRect.Draw(0x0000ff, false);
#endif
}
int Player::ReturnCurrentWeaponIndex()const {
    return _weaponIndex;
}
void Player::CheckHitMap(Rect& chipRect)
{
    // 当たり矩形
    _collisionRect.SetCenter(_pos.x, _pos.y, _scale - 1, _scale - 1);

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
void Player::CheckSpringHitMap(Rect& springRect) {
    if (!_collisionRect.IsCollision(springRect)) return;

    // めり込み量（左右・上下）
    float overlapL = _collisionRect.GetRight() - springRect.GetLeft();   // 左へ押す量
    float overlapR = springRect.GetRight() - _collisionRect.GetLeft(); // 右へ押す量
    float overlapT = _collisionRect.GetBottom() - springRect.GetTop();    // 上へ押す量
    float overlapB = springRect.GetBottom() - _collisionRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (_collisionRect.GetLeft() + _collisionRect.GetRight()) * 0.5f;
    float rcy = (_collisionRect.GetTop() + _collisionRect.GetBottom()) * 0.5f;
    float ccx = (springRect.GetLeft() + springRect.GetRight()) * 0.5f;
    float ccy = (springRect.GetTop() + springRect.GetBottom()) * 0.5f;

    // 壁に当たったのに縦へ押し戻すのを防ぐ
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
                _currentState = PlayerState::Jump;
                _soundPlayer->PlayerCallSE(PlayerState::Jump);
                _jumpAddres->SpringJumpProtocol(*this);
                _isGround = false;
        }
    }
}

void Player::CheckMoveFloorHitMap(Rect& moveFloorRect, VerticalMoveFloor* floor) {
        if (!_collisionRect.IsCollision(moveFloorRect)) return;

    // めり込み量（左右・上下）
    float overlapL = _collisionRect.GetRight() - moveFloorRect.GetLeft();   // 左へ押す量
    float overlapR = moveFloorRect.GetRight() - _collisionRect.GetLeft(); // 右へ押す量
    float overlapT = _collisionRect.GetBottom() - moveFloorRect.GetTop();    // 上へ押す量
    float overlapB = moveFloorRect.GetBottom() - _collisionRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (_collisionRect.GetLeft() + _collisionRect.GetRight()) * 0.5f;
    float rcy = (_collisionRect.GetTop() + _collisionRect.GetBottom()) * 0.5f;
    float ccx = (moveFloorRect.GetLeft() + moveFloorRect.GetRight()) * 0.5f;
    float ccy = (moveFloorRect.GetTop() + moveFloorRect.GetBottom()) * 0.5f;

    // 壁に当たったのに縦へ押し戻すのを防ぐ
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
        //_isGround = true;
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _pos.y -= pushY ;
            _pos.y += floor->GetMoveY();
            //_pos.y = floor->GetPos().y - _scale;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
                _isGround = true;
            }

        }
    }

}

std::unique_ptr<ThrowKnife> Player::CreateKnife() {
    if (_isBlowing) {
        return nullptr;
    }
    if (_weaponIndex != static_cast<int>(WeaponKinds::UseKnife)) {
        return nullptr;
    }
    if (Pad::IsTrigger(PAD_INPUT_3)) {
        //ThrowKnife* knife = new ThrowKnife();
        auto knife = std::make_unique<ThrowKnife>();
        knife->SetInfo(_draw, _isRight);
        _currentState = PlayerState::Throw;
        _isThrowing = true;
        _soundPlayer->PlayerCallSE(PlayerState::Throw);
        return knife;
    }
    return nullptr;
}
std::unique_ptr<Axe> Player::CreateAxe() {
    if (_isBlowing) {
        return nullptr;
    }
    if (_weaponIndex != static_cast<int>(WeaponKinds::UseAxe)) {
        return nullptr;
    }
    if (Pad::IsTrigger(PAD_INPUT_3)) {
        auto axe = std::make_unique<Axe>();
        axe->SetInfo(_draw, _isRight);
        _currentState = PlayerState::Throw;
        _isThrowing = true;
        _soundPlayer->PlayerCallSE(PlayerState::Throw);
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
    _jumpAddres->JumpProtocol(*this,_isMoveing);
	_isGround = false;
    _currentState = PlayerState::Jump;
    _soundPlayer->PlayerCallSE(PlayerState::Jump);
}
void Player::ResetPosition() {
    _pos.x = _initX;
    _pos.y = _initY;
}

void Player::ChangeHandle() {
    switch (_currentState) {
    case PlayerState::Idle:
        _useHandle = _idleHandle;
        break;
    case PlayerState::Move:
        _useHandle = _moveOneHandle;
        break;
    case PlayerState::Jump:
        _useHandle = _jumpHandle;
        break;
    case PlayerState::Throw:
        _useHandle = _throwHandle;
        break;
    case PlayerState::BlowAway:
        _useHandle = _blowAwayHandle;
    //default:
    //    _useHandle = _idleHandle;
        //break;
    }
}

void Player::BlowAway() {
    if (_isBlowRight) {
        _pos.x += _blowAwayPower * _blowAwayMovePixel * ShareClass::KoteiValue;
    }
    else {
        _pos.x -= _blowAwayPower * _blowAwayMovePixel * ShareClass::KoteiValue;
    }
    if (_isGround && _blowTime >0.5f) {
        _isBlowing = false;
    }
    _currentState = PlayerState::BlowAway;
}

void Player::CallBlowAway(bool isRight) {
    _isBlowing = true;
    _blowAwayPower = _initBlowAwayPower;
    _jumpAddres->JumpProtocol(*this, _isMoveing);
    _isGround = false;
    _currentState = PlayerState::BlowAway;
    _isBlowRight = isRight;
    _blowTime = 0;
}