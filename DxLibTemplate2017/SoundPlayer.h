#pragma once
#include "Player.h"
class Player;
class SoundPlayer
{
public:
	SoundPlayer();
	~SoundPlayer();
	void PlayerCallSE(PlayerState state);
	/// <summary>
	/// ゲームのBGMを再生
	/// </summary>
	void PlayGameBGM();
	/// <summary>
	/// 武器が当たった時の効果音
	/// </summary>
	/// <param name="weaponIndex">0が斧、1がナイフ</param>
	void PlayWeaponHitSound(int weaponIndex);
private:
	//ゲームのBGM
	int _bgmHandle;
	//ジャンプの効果音のハンドル
	int _jumpSEHandle;
	//投げる効果音のハンドル
	int _throwSEHandle;
	//ナイフにヒット音
	int _knifeHitSound;
	//斧のヒット音
	int _axeHitSound;

};

