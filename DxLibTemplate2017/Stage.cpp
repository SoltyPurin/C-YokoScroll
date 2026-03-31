#include "Stage.h"
#include "Obstacle.h"
#include "Player.h"
#include "Enemy.h"
#include "AxeEnemy.h"
#include <DxLib.h>
#include <fstream>
#include <sstream>
#include "ThrowAxe.h"
#include "ThrowKnife.h"
#include "VerticalMoveFloor.h"
#include <vector>
#include "Spring.h"
#include "Goal.h"
#include "SoundPlayer.h"

int _backGroundHandler = 0;
namespace
{
	constexpr float MAP_WIDTH = 10000.0f;	 // マップ全体の幅
	constexpr float MAP_HEIGHT = 2080.0f;	 // マップ全体の高さ
	constexpr float SCREEN_WIDTH = 1920.0f;	 // スクリーンの幅
	constexpr float SCREEN_HEIGHT = 1080.0f; // スクリーンの高さ
	constexpr float CHIP_SIZE = 64;

	
	constexpr float kChipScale = 1.5f; 	// マップチップ拡大率

	// チップを置く数
	constexpr int CHIP_NUM_X = MAP_WIDTH / CHIP_SIZE;
	constexpr int CHIP_NUM_Y = MAP_HEIGHT / CHIP_SIZE;

	// マップチップの配列情報
	int CHIP_DATA[CHIP_NUM_Y][CHIP_NUM_X];

	constexpr int WEAPON_MAX = 16;
}
int _bgWidth = static_cast<int>(SCREEN_WIDTH)-1;
int _bgHeight = static_cast<int>(SCREEN_HEIGHT)-1;
Stage::Stage(Player* player,SoundPlayer* sound): 
	_soundPlayer(sound),
	_player(player),
	_graphChipNumX(0),
	_graphChipNumY(0)
{
	_player->SetStagePointer(this);
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		_axe[i] = nullptr;
	}
	for (int i = 0; i < WEAPON_MAX; i++) {
		_knife[i] = nullptr;
	}
	pos = { 0,0 };
	_backGroundHandler = LoadGraph("Image/BackGround.png");
	_mapChipHandle = LoadGraph("Image/mapChip.png");
	_axeHandle = LoadGraph("Image/Axe.png");
	_knifeHandle = LoadGraph("Image/Knife.png");

	int graphW = 0;
	int graphH = 0;
	GetGraphSize(_mapChipHandle, &graphW, &graphH);

	_graphChipNumX = graphW / CHIP_SIZE;
	_graphChipNumY = graphH / CHIP_SIZE;

	LoadMap();
}
Stage::~Stage() {
	DeleteGraph(_backGroundHandler);
	DeleteGraph(_mapChipHandle);
	DeleteGraph(_axeHandle);
	DeleteGraph(_knifeHandle);
}

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

				SpawnEnemy(0, x * CHIP_SIZE*kChipScale, y * CHIP_SIZE * kChipScale);
				CHIP_DATA[y][x] = 0;
			}
			if (CHIP_DATA[y][x] == 6) {//6番をゴールとする
				_goal = new Goal(this,x * CHIP_SIZE * kChipScale, y * CHIP_SIZE * kChipScale);
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



			x++;
		}
		y++;
	}
}

void Stage::SetSpring(float x, float y) {
	Spring* newSpring = new Spring(this);
	_springs.push_back(newSpring);
	newSpring->SetPosition(x, y);
}
void Stage::SetMoveFloor(float x, float y) {
	VerticalMoveFloor* newFloor = new VerticalMoveFloor(this);
	_moveFloors.push_back(newFloor);
	newFloor->SetPosition(x, y);
}

void Stage::SpawnEnemy(int enIndex,float x,float y) {
	switch (enIndex)
	{
	case 0:
	{
		Enemy* newEnemy = new Enemy(this, x, y);
		_enemys.push_back(newEnemy);
		break;
	}
	case 1: {
		AxeEnemy* newAxeEnemy = new AxeEnemy(this, x, y);
		newAxeEnemy->SetPlayerInfo(_player);
		_enemys.push_back(newAxeEnemy);
		break;
	}
	}

}
bool Stage::Update() {
	bool isClear = false;
	//Updateによる計算処理
		for (auto i = _moveFloors.begin(); i != _moveFloors.end();i++) {
		VerticalMoveFloor* floor = *i;
			floor->Update();
		}
		for (auto i = _springs.begin(); i != _springs.end(); i++) {
			Spring* spring = *i;
			spring->Update();
		}
		//敵のUpdate
		for (auto i = _enemys.begin(); i != _enemys.end(); ) {
			Enemy* enemy = *i;
			if (enemy) {
				enemy->Update();
				i++;
			}
			else {
				i = _enemys.erase(i);
			}
		}
		Rect chipRect;
		_player->CheckHitMap(chipRect);
		_player->Update();
		//敵の当たり判定の処理
		for (auto i = _enemys.begin(); i != _enemys.end(); ) {
			Enemy* enemy = *i;
			if (enemy) {
				//敵本体の当たり判定ではなく、仮の世界座標を生成し、敵の座標を世界座標に変換し渡す
				Rect worldEnemyRect;
				worldEnemyRect.m_left = enemy->GetColRect().GetLeft() + GetScrollX();
				worldEnemyRect.m_right = enemy->GetColRect().GetRight() + GetScrollX();
				worldEnemyRect.m_top = enemy->GetColRect().GetTop() + GetScrollY();
				worldEnemyRect.m_bottom = enemy->GetColRect().GetBottom() + GetScrollY();
				Rect tempChipRect;
				if (IsCollision(worldEnemyRect, tempChipRect)) {
					enemy->CheckHitMap(tempChipRect);
				}

				i++;
			}
			else {
				i = _enemys.erase(i);
			}
		}
	DetectPlayerToObstacleCollision();
	DetectPlayerToEnemyCollision();
	if (DetectPlayerToGoalCollision()) {
		isClear = true;
		_isResetting = true;
	}

	UpdateAxe();
	UpdateKnife();
	UpdateEnemyAxe();
	_goal->Update();

	PlayerFallCheck();
	if (_isResetting) {
		ResetGame();
		_isResetting = false;
	}

	return isClear;
}

void Stage::Draw() {
	DrawBackGround();
	DrawMapChip();
	//敵の描画処理
	for (auto i = _enemys.begin(); i != _enemys.end(); ) {
		Enemy* enemy = *i;
		if (enemy) {
			enemy->Draw(GetScrollX(), GetScrollY());
			i++;
		}
		else {
			i = _enemys.erase(i);
		}
	}
	for (auto i = _moveFloors.begin(); i != _moveFloors.end(); i++) {
		VerticalMoveFloor* floor = *i;
		floor->DrawFloor(GetScrollX(), GetScrollY());
	}
	for (auto i = _springs.begin(); i != _springs.end(); i++) {
		Spring* spring = *i;
		spring->DrawSpring(GetScrollX(), GetScrollY());
	}
	_player->Draw();

	DrawAxe();
	DrawKnife();
	DrawEnemyAxe();
	_goal->DrawGoal(GetScrollX(), GetScrollY());

	DrawCurrentWeapon();

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

void Stage::PlayerFallCheck() {
	if (_player->GetPos().y >= _groundY) {
		_isResetting = true;
	}
}
bool Stage::DetectPlayerToGoalCollision() {
	bool isGoal = false;
	bool isPlayerGoalCollision = _goal->GetColRect().IsCollision(_player->GetColRect());
	if (isPlayerGoalCollision) {
		isGoal = true;
	}
	return isGoal;
}
void Stage::DetectPlayerToEnemyCollision() {
	for (auto i = _enemys.begin(); i != _enemys.end();) {
		Enemy* enemy = *i;
		if (enemy) {
			bool isPlayerEnemyCollision = enemy->GetColRect().IsCollision(_player->GetColRect());
			if (isPlayerEnemyCollision) {
				_isResetting = true;
				break;
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
		VerticalMoveFloor* floor = *i;
			bool isPlayerFloorCollision = floor->GetColRect().IsCollision(_player->GetColRect());
			if (isPlayerFloorCollision) {
				_player->CheckObstacleHitMap(floor->GetColRect(),false);
			}

	}

	for (auto i = _springs.begin(); i != _springs.end(); i++) {
		Spring* spring = *i;
		bool isPlayerFloorCollision = spring->GetColRect().IsCollision(_player->GetColRect());
		if (isPlayerFloorCollision) {
			_player->CheckObstacleHitMap(spring->GetColRect(), true);
			spring->ActiveSpring();
		}
	}
}
void Stage::ResetGame() {
	for (int i = 0; i < WEAPON_MAX; i++) {
		DeleteAxe(i);
		DeleteKnife(i);
		DeleteEnemyAxe(i);
	}
	for (auto enemy : _enemys) {
		delete enemy;
	}
	for (auto floor : _moveFloors) {
		delete floor;
	}
	for (auto spring : _springs) {
		delete spring;
	}
	if (_goal != nullptr) {
		delete _goal;
		_goal = nullptr;
	}
	_enemys.clear();
	_moveFloors.clear();
	_springs.clear();
	_player->ResetPosition();
	_soundPlayer->PlayGameBGM(1);
	LoadMap();
}

#pragma region Axe


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

void Stage::UpdateAxe() {
	Axe* newAxe = _player->CreateAxe();
	if (newAxe != nullptr) {
		//斧を生成できた場合は保持
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (_axe[i] == nullptr) {
				_axe[i] = newAxe;
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
			Enemy* enemy = *j;
			if (enemy) {
				isTouchEnemy = _axe[i]->GetColRect().IsCollision(enemy->GetColRect());
				if (isTouchEnemy) {
					//敵を削除
					delete enemy;
					//要素の中身を前につめる
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

	delete _axe[index];
	_axe[index] = nullptr;
}
#pragma endregion

#pragma region EnemyAxe
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
void Stage::UpdateEnemyAxe() {
	for (auto enemy : _enemys) {
		AxeEnemy* axeEnemy = dynamic_cast<AxeEnemy*>(enemy);
		if (!axeEnemy) continue;
		Axe* newAxe = axeEnemy->CreateAxe();
		if (newAxe != nullptr) {
			//斧を生成できた場合は保持
			for (int i = 0; i < WEAPON_MAX; i++)
			{
				if (_enemyAxe[i] == nullptr) {
					_enemyAxe[i] = newAxe;
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
					_isResetting = true;
				}
			}
}

void Stage::DeleteEnemyAxe(int index) {
	if (!_enemyAxe[index]) {
		return;
	}

	delete _enemyAxe[index];
	_enemyAxe[index] = nullptr;
}
#pragma endregion


#pragma region Knife

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
void Stage::UpdateKnife() {
	ThrowKnife* newKnife = _player->CreateKnife();
	if (newKnife != nullptr) {
		//ナイフを生成できた場合は保持
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (_knife[i] == nullptr) {
				_knife[i] = newKnife;
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
		for (auto j = _enemys.begin(); j != _enemys.end();) {
			Enemy* enemy = *j;
			if (enemy) {
				isTouchEnemy = _knife[i]->GetColRect().IsCollision(enemy->GetColRect());
				if (isTouchEnemy) {
					delete enemy;
					j = _enemys.erase(j);
					_soundPlayer->PlayWeaponHitSound(1);
					break;

				}
				else {
					j++;
				}
			}
		}

		if (isOutOfScreen || isTouchEnemy)
		{
			DeleteKnife(i);
		}
	}

}

void Stage::DeleteKnife(int index) {
	if (!_knife[index]) {
		return;
	}

	delete _knife[index];
	_knife[index] = nullptr;
}
#pragma endregion


void Stage::DrawBackGround() {
	GetGraphSize(_backGroundHandler,&_bgWidth , &_bgHeight);
	int scrollBg = GetScrollX() % _bgWidth;
	DrawGraph(-scrollBg, pos.y, _backGroundHandler, true);
	//DrawExtendGraph(scrollBg, 0, scrollBg+SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, _backGroundHandler, TRUE);
	if (scrollBg > 0)
	{
		DrawGraph(_bgWidth - scrollBg, SCREEN_HEIGHT - _bgHeight, _backGroundHandler, true);
	}
}
void Stage::DrawMapChip() {
	//DrawGraph(0, 0, _mapHandle, true);
	// マップチップの描画
	for (int y = 0; y < CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < CHIP_NUM_X; x++)
		{
			int posX = static_cast<int>(x * CHIP_SIZE * kChipScale - GetScrollX());
			int posY = static_cast<int>(y * CHIP_SIZE * kChipScale - GetScrollY());

			// 画面外は描画しない
			if (posX < 0 - CHIP_SIZE) continue;
			if (posX > SCREEN_WIDTH) continue;
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
int Stage::GetScrollX() {
	int result = static_cast<int>(_player->GetPos().x - SCREEN_WIDTH * 0.5);
	if (result < 0)
	{
		result = 0;
	}
	if (result > MAP_WIDTH - SCREEN_WIDTH)
	{
		result = MAP_WIDTH - SCREEN_WIDTH;
	}

	return result;
}

int Stage::GetScrollY() {
	int result = static_cast<int>(_player->GetPos().y - SCREEN_HEIGHT * 0.5f);
	if (result < 0) {
		result = 0;
	}
	if (result > MAP_HEIGHT - SCREEN_HEIGHT) {
		result = MAP_HEIGHT - SCREEN_HEIGHT;
	}

	return result;
}