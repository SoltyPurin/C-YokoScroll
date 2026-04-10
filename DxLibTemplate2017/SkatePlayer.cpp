#include "DxLib.h"
#include "SkatePlayer.h"
#include "Player.h"
#include "ShareClass.h"
SkatePlayer::SkatePlayer(float x,float y,NormalPlayerImages nImage,SkatePlayerImages images)
	:Player(x,y,nImage),
_rideSkateHandle(images._ride),
_brakeSkateHandle(images._brake),
_moveUseValue(_notInputOnePixelMoveValue){
	_isMoveing = true;
}

SkatePlayer::~SkatePlayer() {
	//DeleteGraph(_brakeSkateHandle);
	//DeleteGraph(_rideSkateHandle);
	//DeleteGraph(_useHandle);
}

void SkatePlayer::Update() {
	Gravity(ShareClass::DeltaTime);
	_pos.y -= _verticalY * _oneMinuteMovePixel * ShareClass::DeltaTime;
	_pos.x += _move.x * _moveUseValue* ShareClass::DeltaTime;
	_collisionRect.SetCenter(_draw.x + _scale * 0.5f, _draw.y + _scale * 0.5f, _scale * 0.5f, _scale);
	if (_isThrowing) {
		_currentThrowingTime += ShareClass::DeltaTime;
		_currentState = PlayerState::Throw;
	}
	if (_currentThrowingTime >= _throwStateTime) {
		_currentThrowingTime = 0;
		_isThrowing = false;
	}

}

void SkatePlayer::Draw() {
	ChangeHandle();
	_draw.x = _pos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
	_draw.y = _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f;
	DrawExtendGraph(_draw.x, _draw.y, _draw.x + _scale, _draw.y + _scale, _useHandle, TRUE);

}

void SkatePlayer::Move(float moveValue, bool isRight) {
	_move.x = abs(moveValue);
	if (moveValue > 0) { //‰E“ü—Í
		_moveUseValue = _inputOnePixelMoveValue;
		_isBrake = false;
	}
	else if (moveValue < 0) { //¶“ü—Í
		_moveUseValue = _brakeOnePixelMoveValue;
		_isBrake = true;
	}
	else {//–³“ü—Í
		_move.x = 5;
		_moveUseValue = _notInputOnePixelMoveValue;
		_isBrake = false;
	}
}

void SkatePlayer::ChangeHandle() {
	if (_isBrake) {
		_useHandle = _brakeSkateHandle;
	}
	else {
		_useHandle = _rideSkateHandle;
	}
}