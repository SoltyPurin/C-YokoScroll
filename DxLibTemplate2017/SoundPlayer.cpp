#include "SoundPlayer.h"
#include "DxLib.h"
#include "Player.h"
SoundPlayer::SoundPlayer() {
	_jumpSEHandle = LoadSoundMem("Audio/SE/Jump.mp3");
	_throwSEHandle = LoadSoundMem("Audio/SE/Throw.wav");
	_bgmHandle = LoadSoundMem("Audio/BGM/GameBGM.wav");
	_axeHitSound = LoadSoundMem("Audio/SE/AxeHit.mp3");
	_knifeHitSound = LoadSoundMem("Audio/SE/KnifeHit.mp3");
}
SoundPlayer::~SoundPlayer() {
	DeleteSoundMem(_jumpSEHandle);
	DeleteSoundMem(_throwSEHandle);
	DeleteSoundMem(_bgmHandle);
	DeleteSoundMem(_axeHitSound);
	DeleteSoundMem(_knifeHitSound);
}
void SoundPlayer::PlayGameBGM() {
	if (CheckSoundMem(_bgmHandle)) {
		StopSoundMem(_bgmHandle);
	}
	PlaySoundMem(_bgmHandle, DX_PLAYTYPE_LOOP);
}

void SoundPlayer::PlayWeaponHitSound(int weaponIndex) {
	switch (weaponIndex)
	{
	case 0:
		PlaySoundMem(_axeHitSound, DX_PLAYTYPE_BACK);
		break;

	case 1:
		PlaySoundMem(_knifeHitSound, DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
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


