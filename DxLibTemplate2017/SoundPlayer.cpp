#include "Precompile.h"
#include "SoundPlayer.h"
#include "Player.h"
SoundPlayer::SoundPlayer() {
	_jumpSEHandle = LoadSoundMem("Audio/SE/Jump.mp3");
	_throwSEHandle = LoadSoundMem("Audio/SE/Throw.wav");
	_axeHitSound = LoadSoundMem("Audio/SE/AxeHit.mp3");
	_knifeHitSound = LoadSoundMem("Audio/SE/KnifeHit.mp3");
	_gameBGMHandle = LoadSoundMem("Audio/BGM/GameBGM.wav");
	_titleBGMHandle = LoadSoundMem("Audio/BGM/TitleBGM.wav");
	_clearBGMHandle = LoadSoundMem("Audio/BGM/ClearBGM.wav");
}
SoundPlayer::~SoundPlayer() {
	DeleteSoundMem(_jumpSEHandle);
	DeleteSoundMem(_throwSEHandle);
	DeleteSoundMem(_axeHitSound);
	DeleteSoundMem(_knifeHitSound);
	DeleteSoundMem(_gameBGMHandle);
	DeleteSoundMem(_titleBGMHandle);
}
void SoundPlayer::PlayGameBGM(int index) {
	StopSoundMem(_titleBGMHandle);
	StopSoundMem(_gameBGMHandle);
	StopSoundMem(_clearBGMHandle);
	switch (index)
	{
	case 0:
		PlaySoundMem(_titleBGMHandle, DX_PLAYTYPE_LOOP);
		break;
	case 1:
		PlaySoundMem(_gameBGMHandle, DX_PLAYTYPE_LOOP);
		break;
	case 2:
		PlaySoundMem(_clearBGMHandle, DX_PLAYTYPE_LOOP);
		break;
	default:
		break;
	}
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


