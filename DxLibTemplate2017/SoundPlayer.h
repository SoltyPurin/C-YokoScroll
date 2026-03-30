#pragma once
#include "Player.h"
class Player;
class SoundPlayer
{
public:
	SoundPlayer();
	~SoundPlayer();
	void PlayerCallSE(PlayerState state);
private:
	//ゲームのBGM
	int _bgmHandle;
	//ジャンプの効果音のハンドル
	int _jumpSEHandle;
	//投げる効果音のハンドル
	int _throwSEHandle;

};

