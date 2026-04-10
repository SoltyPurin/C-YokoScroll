#include "PlayerInputManager.h"
#include "Pad.h"
#include <DxLib.h>
#include "Player.h"

PlayerInputManager::PlayerInputManager(Player* player):
_player(player){
}
PlayerInputManager::~PlayerInputManager() {

}
void PlayerInputManager::Update() {
	Pad::Update();
    GetHitKeyStateAll(_keyState);
    // プレイヤーの移動処理
    if (Pad::IsPress(PAD_INPUT_RIGHT) || _keyState[KEY_INPUT_RIGHT]) {
        _isRight = true;
        _player->Move(_moveValue, _isRight);
    }
    else if (Pad::IsPress(PAD_INPUT_LEFT) || _keyState[KEY_INPUT_LEFT]) {
        _isRight = false;
        _player->Move(-_moveValue, _isRight);
    }
    else {
        _player->Move(0, _isRight);
    }

    // プレイヤーのジャンプ・攻撃処理
    if (Pad::IsPress(PAD_INPUT_1) || _keyState[KEY_INPUT_SPACE]) {
        _player->JumpProtocol();
    }
    if (Pad::IsTrigger(PAD_INPUT_2)) {
        _player->ChangeWeapon();
    }

}
