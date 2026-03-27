#pragma once
#include "Enemy.h"
class ThrowAxe;
class Player;
class AxeEnemy : public Enemy
{
public:
	AxeEnemy(Stage* stage, float x, float y);
	~AxeEnemy();
	void SetPlayerInfo(Player* player) { _playerInfo = player; }
	virtual void Update()override;
    Axe* CreateAxe();
	bool IsPlayerRight();

private:
	/// <summary>
	/// 斧を投げてからの経過時間
	/// </summary>
	float _currentThrowingTime = 0;
	/// <summary>
	/// 次に斧を投げる時間
	/// </summary>
	float _nextThrowTime = 3;
	/// <summary>
	/// プレイヤー参照
	/// </summary>
	Player* _playerInfo;

};

