#pragma once
#include "Player.h"
class Jump
{
public:
	void JumpProtocol(Player& player, bool isMove);
	void SpringJumpProtocol(Player& player);
private:
	float _moveingJumpPower = 5.5f;
	float _idlingJumpPower = 3.5f;
	float _springJumpPower = 10.0f;

};

