#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "VerticalMoveFloor.h"
#include "ThrowKnife.h"
#include "ThrowAxe.h"
#include "Skate.h"
#include "Enemy.h"
#include "Goal.h"
#include "Stone.h"
#include "Spring.h"

void Stage::Draw() {
	DrawBackGround();
	DrawMapChip();
	//敵の描画処理
	for (auto i = _enemys.begin(); i != _enemys.end(); ) {
		if (*i) {
			(*i)->Draw(GetScrollX(), GetScrollY());
			i++;
		}
		else {
			i = _enemys.erase(i);
		}
	}
	for (auto i = _moveFloors.begin(); i != _moveFloors.end(); i++) {
		if (*i) {
			(*i)->DrawFloor(GetScrollX(), GetScrollY());
		}
	}
	for (auto i = _springs.begin(); i != _springs.end(); i++) {
		if (*i) {
			(*i)->DrawSpring(GetScrollX(), GetScrollY());
		}
	}
	for (auto i = _skates.begin(); i != _skates.end(); i++) {
		if (*i) {
			(*i)->DrawSkateBoard(GetScrollX(), GetScrollY());
		}
	}
	for (auto i = _stones.begin(); i != _stones.end(); i++) {
		if (*i) {
			(*i)->Draw(GetScrollX(), GetScrollY());
		}
	}
	_player->Draw();

	DrawAxe();
	DrawKnife();
	DrawEnemyAxe();
	_goal->DrawGoal(GetScrollX(), GetScrollY());

	DrawCurrentWeapon();

	DrawExtendGraph(0, 0, 100, 100, _rideSkateIndex, TRUE);
	DrawExtendGraph(0, 100, 100, 200, _brakeSkateIndex, TRUE);

}

void Stage::DrawCurrentWeapon() {
	int curWeapon = _player->ReturnCurrentWeaponIndex();
	switch (curWeapon)
	{
	case 0:
		DrawGraph(0, 0, _axeHandle, TRUE);
		break;

	case 1:
		DrawGraph(0, 0, _knifeHandle, TRUE);
		break;
	default:
		DrawGraph(0, 0, _knifeHandle, TRUE);
		break;
	}
}
void Stage::DrawAxe() {
	if (!_axe) {
		return;
	}
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_axe[i]) continue;
		_axe[i]->DrawWeapon();
	}
}
void Stage::DrawEnemyAxe() {
	if (!_enemyAxe) {
		return;
	}
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_enemyAxe[i]) continue;
		_enemyAxe[i]->DrawWeapon();
	}
}

void Stage::DrawKnife() {
	if (!_knife) {
		return;
	}
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		if (!_knife[i]) continue;
		_knife[i]->DrawWeapon();
	}
}
void Stage::DrawBackGround() {
	GetGraphSize(_backGroundHandler, &_bgWidth, &_bgHeight);
	int scrollBg = GetScrollX() % _bgWidth;
	DrawGraph(-scrollBg, pos.y, _backGroundHandler, true);
	if (scrollBg > 0)
	{
		DrawGraph(_bgWidth - scrollBg, SCREEN_HEIGHT - _bgHeight, _backGroundHandler, true);
	}
}
void Stage::DrawMapChip() {
	// マップチップの描画
	for (int y = 0; y < CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < CHIP_NUM_X; x++)
		{
			int posX = static_cast<int>(x * CHIP_SIZE * kChipScale - GetScrollX());
			int posY = static_cast<int>(y * CHIP_SIZE * kChipScale - GetScrollY());

			// 画面外は描画しない
			if (posX < 0 - CHIP_SIZE-CHIP_SIZE) continue;
			if (posX > SCREEN_WIDTH+CHIP_SIZE) continue;
			if (posY < 0 - CHIP_SIZE) continue;
			if (posY > SCREEN_HEIGHT) continue;

			// 設置するチップ
			int chipNo = CHIP_DATA[y][x];

			// マップチップのグラフィック切り出し座標
			int srcX = CHIP_SIZE * (chipNo % _graphChipNumX);
			int srcY = CHIP_SIZE * (chipNo % _graphChipNumY);

			// 描画
			DrawRectRotaGraph(
				static_cast<int>(posX + CHIP_SIZE * kChipScale * 0.5f),
				static_cast<int>(posY + CHIP_SIZE * kChipScale * 0.5f),
				srcX, srcY,
				CHIP_SIZE, CHIP_SIZE,
				kChipScale, 0.0f,
				_mapChipHandle, true);


#ifdef _DEBUG
			// 当たり判定
			DrawBoxAA(posX, posY, posX + CHIP_SIZE * kChipScale, posY + CHIP_SIZE * kChipScale, 0x00ff00, false);
#endif
		}
	}
}


