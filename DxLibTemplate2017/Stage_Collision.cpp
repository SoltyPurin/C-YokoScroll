#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "VerticalMoveFloor.h"
#include "Skate.h"
#include "Enemy.h"
#include "Goal.h"
#include "Stone.h"
#include "Spring.h"

bool Stage::DetectPlayerToGoalCollision() {
	bool isGoal = false;
	bool isPlayerGoalCollision = _goal->GetColRect().IsCollision(_player->GetColRect());
	if (isPlayerGoalCollision) {
		isGoal = true;
	}
	return isGoal;
}

bool Stage::DetectPlayerToSkateCollision() {
	bool isCollisionSkate = false;
	for (auto i = _skates.begin(); i != _skates.end(); i++) {
		if (*i) {
			bool isPlayerSkateCollision = (*i)->GetColRect().IsCollision(_player->GetColRect());

			if (isPlayerSkateCollision) {
				i = _skates.erase(i);
				isCollisionSkate = true;
				break;
			}

		}
		else {
			i = _skates.erase(i); // 無効なポインタなら削除して次へ
		}
	}
	return isCollisionSkate;
}
void Stage::DetectPlayerToEnemyCollision() {
	for (auto i = _enemys.begin(); i != _enemys.end();) {
		if ((*i)) {
			bool isPlayerEnemyCollision = (*i)->GetColRect().IsCollision(_player->GetColRect());
			if (isPlayerEnemyCollision) {
				if (_isSkateing) {
					_enemys.erase(i);
					SwitchPlayerState(false, _player->GetPos());
					_player->CallBlowAway(!_player->IsPlayerRight());
					break;
				}
				else {
					_isResetting = true;
					break;
				}
			}
			i++;
		}
		else {
			i = _enemys.erase(i);
		}
	}
}
void Stage::DetectPlayerToObstacleCollision() {
	for (auto i = _moveFloors.begin(); i != _moveFloors.end(); i++) {
		_player->CheckMoveFloorHitMap((*i)->GetColRect(), (*i).get());
	}

	for (auto i = _springs.begin(); i != _springs.end(); i++) {
		bool isPlayerFloorCollision = (*i)->GetColRect().IsCollision(_player->GetColRect());
		if (isPlayerFloorCollision) {
			_player->CheckSpringHitMap((*i)->GetColRect());
			(*i)->ActiveSpring();
		}
	}
	for (auto i = _stones.begin(); i != _stones.end(); i++) {
		bool isStoneCollision = (*i)->GetColRect().IsCollision(_player->GetColRect());
		if (isStoneCollision) {
			if (_isSkateing) {
				SwitchPlayerState(false, _player->GetPos());
			}
			_player->CallBlowAway(_player->IsPlayerRight());
		}
	}
}

bool Stage::IsCollision(Rect rect, Rect& chipRect)
{
	bool hit = false;

	// rectの中心（距離評価用）
	const float rcx = (rect.GetLeft() + rect.GetRight()) * 0.5f;
	const float rcy = (rect.GetTop() + rect.GetBottom()) * 0.5f;

	float bestDist2 = 0.0f;

	for (int y = 0; y < CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < CHIP_NUM_X; x++)
		{
			if (CHIP_DATA[y][x] == 0) continue;
			if (CHIP_DATA[y][x] == 6) continue;

			const int chipLeft = static_cast<int>(x * CHIP_SIZE * kChipScale);
			const int chipRight = static_cast<int>(chipLeft + CHIP_SIZE * kChipScale);
			const int chipTop = static_cast<int>(y * CHIP_SIZE * kChipScale);
			const int chipBottom = static_cast<int>(chipTop + CHIP_SIZE * kChipScale);

			// AABB 非交差ならスキップ
			if (chipLeft > rect.GetRight())  continue;
			if (chipTop > rect.GetBottom()) continue;
			if (chipRight < rect.GetLeft())   continue;
			if (chipBottom < rect.GetTop())    continue;

			// このチップの中心
			const float ccx = (chipLeft + chipRight) * 0.5f;
			const float ccy = (chipTop + chipBottom) * 0.5f;

			const float dx = ccx - rcx;
			const float dy = ccy - rcy;
			const float dist2 = dx * dx + dy * dy;

			// 最も近い衝突チップを採用
			if (!hit || dist2 < bestDist2)
			{
				hit = true;
				bestDist2 = dist2;

				chipRect.m_left = static_cast<float>(chipLeft);
				chipRect.m_right = static_cast<float>(chipRight);
				chipRect.m_top = static_cast<float>(chipTop);
				chipRect.m_bottom = static_cast<float>(chipBottom);

				_colChipIndex = CHIP_DATA[y][x];
			}
		}
	}
	return hit;

}

