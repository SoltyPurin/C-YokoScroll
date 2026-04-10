#pragma once
#include "Player.h"
#include "ShareClass.h"
class SkatePlayer : public Player
{
public:
	SkatePlayer(float x,float y, NormalPlayerImages nImage,SkatePlayerImages images);
	virtual ~SkatePlayer() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Move(float moveValue, bool isRight) override;
	virtual void ChangeHandle() override;
private:
	int _rideSkateHandle;
	int _brakeSkateHandle;
	//入力ナシの時の一秒間に進む距離
	float _notInputOnePixelMoveValue = 150.0f;
	//右入力をしている時の一秒間に進む距離
	float _inputOnePixelMoveValue = 200.0f;
	//ブレーキをしている時の一秒間に進む距離
	float _brakeOnePixelMoveValue = 50.0f;
	//実際の移動に使う変数、この中を差し替えて移動させる
	float _moveUseValue = 0;

	bool _isBrake = false;
};

