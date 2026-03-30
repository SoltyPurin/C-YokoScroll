#include "SoundPlayer.h"
#include "DxLib.h"
#include "Player.h"
SoundPlayer::SoundPlayer() {
	_jumpSEHandle = LoadSoundMem("Audio/SE/Jump.mp3");
	_throwSEHandle = LoadSoundMem("Audio/SE/Throw.wav");
	_bgmHandle = LoadSoundMem("Audio/BGM/GameBGM.wav");
	PlaySoundMem(_bgmHandle, DX_PLAYTYPE_LOOP);
}
SoundPlayer::~SoundPlayer() {
	DeleteSoundMem(_jumpSEHandle);
	DeleteSoundMem(_throwSEHandle);
	DeleteSoundMem(_bgmHandle);
}

void SoundPlayer::PlayerCallSE(PlayerState state) {
	switch (state)
	{
	case PlayerState::Idle:
		break;
	case PlayerState::Move:
		break;
	case PlayerState::Jump:
		if (CheckSoundMem(_jumpSEHandle) == 1) {
			return;
		}
		PlaySoundMem(_jumpSEHandle, DX_PLAYTYPE_BACK);
		break;
	case PlayerState::Throw:
		PlaySoundMem(_throwSEHandle, DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
}


