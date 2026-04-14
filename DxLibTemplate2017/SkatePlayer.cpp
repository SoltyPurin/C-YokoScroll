#include "DxLib.h"
#include "SkatePlayer.h"
#include "Player.h"
#include "ShareClass.h"
SkatePlayer::SkatePlayer(float x,float y,PlayerImages image)
	:Player(x,y,image),
_rideSkateHandle(image._skateRide),
_brakeSkateHandle(image._skateBrake),
_moveUseValue(_notInputOnePixelMoveValue){
	_isMoveing = true;
}

SkatePlayer::~SkatePlayer() {
	//DeleteGraph(_brakeSkateHandle);
	//DeleteGraph(_rideSkateHandle);
	//DeleteGraph(_useHandle);
}

void SkatePlayer::Update() {
	if (_isBlowing) {
		BlowAway();
	}
	else {
		_pos.x += _move.x * _moveUseValue * ShareClass::KoteiValue;
	}
	Gravity(ShareClass::KoteiValue);
	_pos.y -= _verticalY * _oneMinuteMovePixel * ShareClass::KoteiValue;
	_collisionRect.SetCenter(_draw.x + _scale * 0.5f, _draw.y + _scale * 0.5f, _scale * 0.5f, _scale);
	if (_isThrowing) {
		_currentThrowingTime += ShareClass::KoteiValue;
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
	if (_isBlowing) {
		return;
	}
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