#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "ThrowAxe.h"
#include "ThrowKnife.h"
#include "SoundPlayer.h"
#include "AxeEnemy.h"
#include "Stone.h"
#pragma region Axe

void Stage::UpdateAxe() {
	auto newAxe = _player->CreateAxe();
	if (newAxe != nullptr) {
		//斧を生成できた場合は保持
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (_axe[i] == nullptr) {
				_axe[i] = std::move(newAxe);
				break;
			}
		}
	}

	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_axe[i]) continue;

		_axe[i]->Update();

		// 画面外に出たら削除する
		bool isOutOfScreen = _axe[i]->GetPos().x < 0 || _axe[i]->GetPos().x > SCREEN_WIDTH;
		bool isTouchEnemy = false;
		for (auto j = _enemys.begin(); j != _enemys.end();) {
			if ((*j)) {
				isTouchEnemy = _axe[i]->GetColRect().IsCollision((*j)->GetColRect());
				if (isTouchEnemy) {
					//敵を削除
					j = _enemys.erase(j);
					_soundPlayer->PlayWeaponHitSound(0);
					break;

				}
				else {
					j++;
				}
			}
		}

		if (isOutOfScreen || isTouchEnemy)
		{
			DeleteAxe(i);
		}
	}

}

void Stage::DeleteAxe(int index) {
	if (!_axe[index]) {
		return;
	}

	_axe[index].reset();
}
#pragma endregion

#pragma region EnemyAxe
void Stage::UpdateEnemyAxe() {
	for (auto& enemy : _enemys) {
		AxeEnemy* axeEnemy = dynamic_cast<AxeEnemy*>(enemy.get());
		if (!axeEnemy) continue;
		auto newAxe = axeEnemy->CreateAxe();
		if (newAxe != nullptr) {
			//斧を生成できた場合は保持
			for (int i = 0; i < WEAPON_MAX; i++)
			{
				if (_enemyAxe[i] == nullptr) {
					_enemyAxe[i] = std::move(newAxe);
					break;
				}
			}
		}
	}
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_enemyAxe[i]) continue;

		_enemyAxe[i]->Update();

		// 画面外に出たら削除する
		bool isOutOfScreen = _enemyAxe[i]->GetPos().x < 0 || _enemyAxe[i]->GetPos().x > SCREEN_WIDTH;
		bool isTouchPlayer = false;
		isTouchPlayer = _enemyAxe[i]->GetColRect().IsCollision(_player->GetColRect());
		if (isOutOfScreen || isTouchPlayer)
		{
			DeleteEnemyAxe(i);
		}
		if (isTouchPlayer) {
			if (_isSkateing) {
				DeleteEnemyAxe(i);
				SwitchPlayerState(false, _player->GetPos());
				_player->CallBlowAway(!_player->IsPlayerRight());
			}
			else {
				_isResetting = true;
			}
		}
	}
}

void Stage::DeleteEnemyAxe(int index) {
	if (!_enemyAxe[index]) {
		return;
	}

	_enemyAxe[index].reset();
}
#pragma endregion


#pragma region Knife

void Stage::UpdateKnife() {
	auto newKnife = _player->CreateKnife();
	if (newKnife != nullptr) {
		//ナイフを生成できた場合は保持
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (_knife[i] == nullptr) {
				_knife[i] = std::move(newKnife);
				break;
			}
		}
	}

	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_knife[i]) continue;

		_knife[i]->Update();

		// 画面外に出たら削除する
		bool isOutOfScreen = _knife[i]->GetPos().x < 0 || _knife[i]->GetPos().x > SCREEN_WIDTH;
		bool isTouchEnemy = false;
		bool isTouchStone = false;
		for (auto j = _enemys.begin(); j != _enemys.end();) {
			if ((*j)) {
				isTouchEnemy = _knife[i]->GetColRect().IsCollision((*j)->GetColRect());
				if (isTouchEnemy) {
					j = _enemys.erase(j);
					_soundPlayer->PlayWeaponHitSound(1);
					break;

				}
				else {
					j++;
				}
			}
		}
		for (auto j = _stones.begin(); j != _stones.end(); j++) {
			if (*j) {
				isTouchStone = _knife[i]->GetColRect().IsCollision((*j).get()->GetColRect());

			}
			if (isTouchStone) {
				break;
			}
		}
		if (isOutOfScreen || isTouchEnemy || isTouchStone)
		{
			DeleteKnife(i);
		}
	}

}

void Stage::DeleteKnife(int index) {
	if (!_knife[index]) {
		return;
	}

	_knife[index].reset();
}
#pragma endregion

