#include "Jump.h"

float _jumpPower = 1.5f;
void Jump::JumpProtocol(Player& player) {
	float vy = player.ReturnVY();
	vy += _jumpPower;
	player.SetVY(vy);
}
