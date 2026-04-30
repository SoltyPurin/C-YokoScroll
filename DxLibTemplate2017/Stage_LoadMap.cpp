#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "VerticalMoveFloor.h"
#include "Skate.h"
#include "AxeEnemy.h"
#include "Goal.h"
#include "Stone.h"
#include "Spring.h"
void Stage::LoadMap() {
	std::ifstream file("CSV/TestMapData.csv");
	std::string line;

	// getline関数で1行ずつ読み込む
	int y = 0;
	while (std::getline(file, line) && y < CHIP_NUM_Y)
	{
		std::istringstream stream(line);
		std::string field;

		// 「,」区切りごとにデータを読み込む
		int x = 0;
		while (getline(stream, field, ',') && x < CHIP_NUM_X)
		{

			// 文字列をint型に変換してm_chipDataに追加する
			CHIP_DATA[y][x] = std::stoi(field);

			if (CHIP_DATA[y][x] == 5) { // 5番を敵配置チップとする
				//// チップの左上座標を計算

				SpawnEnemy(0, x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}
			if (CHIP_DATA[y][x] == 6) {//6番をゴールとする
				_goal = std::make_unique<Goal>(this, x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}
			//移動床を生成
			if (CHIP_DATA[y][x] == 8) {//8番を移動床とする
				SetMoveFloor(x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}

			if (CHIP_DATA[y][x] == 9) {//9番を非発動バネとする
				SetSpring(x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}

			if (CHIP_DATA[y][x] == 10) {//10番を斧敵とする
				SpawnEnemy(1, x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}

			if (CHIP_DATA[y][x] == 11) {//11番はスケボーとする
				SetSkate(x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}

			if (CHIP_DATA[y][x] == 4) {//4番はこける岩とする
				SetFellStone(x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}

			x++;
		}
		y++;
	}
}
void Stage::SetFellStone(float x, float y) {
	_stones.push_back(std::make_unique<Stone>(_stoneHandle, this, Vector2(x, y)));
}
void Stage::SetSkate(float x, float y) {
	_skates.push_back(std::make_unique<Skate>(this, x, y));
}
void Stage::SetSpring(float x, float y) {
	_springs.push_back(std::make_unique<Spring>(this, x, y));
}
void Stage::SetMoveFloor(float x, float y) {

	_moveFloors.push_back(std::make_unique<VerticalMoveFloor>(this, x, y));
}
void Stage::SpawnEnemy(int enIndex, float x, float y) {
	switch (enIndex)
	{
	case 0:
	{
		_enemys.push_back(std::make_unique<Enemy>(this, x, y));
		break;
	}
	case 1: {
		auto newAxeEnemy = std::make_unique<AxeEnemy>(this, x, y);
		newAxeEnemy->SetPlayerInfo(_player);
		_enemys.push_back(std::move(newAxeEnemy));
		break;
	}
	}

}
