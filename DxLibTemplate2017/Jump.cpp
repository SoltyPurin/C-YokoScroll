#include "Jump.h"

float _jumpPower = 5.5f;
void Jump::JumpProtocol(Player& player) {
	//float vy = player.ReturnVY();
	//vy += _jumpPower;
	player.SetVY(_jumpPower);
}
