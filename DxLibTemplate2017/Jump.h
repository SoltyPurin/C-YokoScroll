#pragma once
#include "Player.h"
class Jump
{
public:
	/// <summary>
	/// 通常のジャンプ処理
	/// </summary>
	/// <param name="player">プレイヤーのポインター</param>
	/// <param name="isMove">移動してるかどうかのフラグ</param>
	void JumpProtocol(Player& player, bool isMove);
	/// <summary>
	/// バネでジャンプした時の処理
	/// </summary>
	/// <param name="player">プレイヤーのポインター</param>
	void SpringJumpProtocol(Player& player);
private:
	float _moveingJumpPower = 5.5f;
	float _idlingJumpPower = 3.5f;
	float _springJumpPower = 10.0f;

};

