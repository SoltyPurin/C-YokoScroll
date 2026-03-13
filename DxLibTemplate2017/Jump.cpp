#include "Jump.h"

float _jumpPower = 5.5f;
float _springJumpPower = 10.0f;
void Jump::JumpProtocol(Player& player) {
	player.SetVY(_jumpPower);
}

void Jump::SpringJumpProtocol(Player& player) {
	player.SetVY(_springJumpPower);
}
