#include "Jump.h"

int _jumpPower = 10;
void Jump::JumpProtocol(Player player) {
	int vy = player.ReturnVY();
	vy += _jumpPower;
	player.SetVY(vy);
}
