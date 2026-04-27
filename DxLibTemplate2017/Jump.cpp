#include "Precompile.h"
#include "Jump.h"

void Jump::JumpProtocol(Player& player, bool isMove) {
	if (isMove) {
		player.SetVY(_moveingJumpPower);
	}
	else {
		player.SetVY(_idlingJumpPower);
	}
}

void Jump::SpringJumpProtocol(Player& player) {
	player.SetVY(_springJumpPower);
}
