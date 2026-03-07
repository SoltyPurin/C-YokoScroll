#include "Stage.h"
#include "Obstacle.h"
#include "Player.h"
#include "Enemy.h"
#include <DxLib.h>
#include <fstream>
#include <sstream>
#include "ThrowAxe.h"

int _backGroundHandler = 0;
namespace
{
	constexpr float MAP_WIDTH = 5000.0f;	 // マップ全体の幅
	constexpr float MAP_HEIGHT = 1080.0f;	 // マップ全体の高さ
	constexpr float SCREEN_WIDTH = 1920.0f;	 // スクリーンの幅
	constexpr float SCREEN_HEIGHT = 1080.0f; // スクリーンの高さ
	constexpr int CHIP_SIZE = 64;

	
	constexpr float kChipScale = 1.5f; 	// マップチップ拡大率

	// チップを置く数
	constexpr int CHIP_NUM_X = MAP_WIDTH / CHIP_SIZE;
	constexpr int CHIP_NUM_Y = SCREEN_HEIGHT / CHIP_SIZE;

	// マップチップの配列情報
	int CHIP_DATA[CHIP_NUM_Y][CHIP_NUM_X];

	constexpr int AXE_MAX = 16;
}
int _bgWidth = static_cast<int>(SCREEN_WIDTH)-1;
int _bgHeight = static_cast<int>(SCREEN_HEIGHT)-1;
Stage::Stage(Player* player) :
	_player(player),
	_graphChipNumX(0),
	_graphChipNumY(0)
{
	_player->SetStagePointer(this);
	_enemy = new Enemy;
	_enemy->SetStagePointer(this);
	for (int i = 0; i < AXE_MAX; i++)
	{
		_axe[i] = nullptr;
	}
	pos = { 0,0 };
	_backGroundHandler = LoadGraph("Image/BackGround.jpg");
	_mapChipHandle = LoadGraph("Image/mapChip.png");

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
			x++;
		}
		y++;
	}
}
void Stage::Update() {
	DrawBackGround();
	DrawMapChip();
	UpdateAxe();
	PlayerFallCheck();
	DetectPlayerToEnemyCollision();
	Rect chipRect;
	if (IsCollision(_player->ReturnRect(), chipRect)) {
		_player->CheckHitMap(chipRect);
	}
	if (_enemy) {
		if (_enemy) {
			_enemy->Update();
		}

		if (IsCollision(_enemy->ReturnRect(), chipRect)) {
			_enemy->CheckHitMap(chipRect);
		}
	}
}

void Stage::PlayerFallCheck() {
	if (_player->GetPos().y >= _groundY) {
		ResetGame();
	}
}

void Stage::DetectPlayerToEnemyCollision() {
	if (_enemy) {
		bool isPlayerEnemyCollision = _enemy->GetColRect().IsCollision(_player->GetColRect());
		if (isPlayerEnemyCollision) {
			ResetGame();
		}
	}
}

void Stage::ResetGame() {
	for (int i = 0; i < AXE_MAX; i++)
	{
		if (!_axe[i]) continue;
		delete _axe[i];
		_axe[i] = nullptr;
	}
	_player->ResetPosition();
	if (_enemy) {
		_enemy->ResetPosition();
	}
	else {
		_enemy = new Enemy;
	}
}

void Stage::DrawAxe() {
	if (!_axe) {
		return;
	}
	for (int i = 0; i < AXE_MAX; i++)
	{
		if (!_axe[i]) continue;
		_axe[i]->DrawWeapon();
	}
}

void Stage::UpdateAxe() {
	Axe* newAxe = _player->CreateAxe();
	if (newAxe != nullptr) {
		//斧を生成できた場合は保持
		for (int i = 0; i < AXE_MAX; i++)
		{
			if (_axe[i] == nullptr) {
				_axe[i] = newAxe;
				break;
			}
		}
	}

	for (int i = 0; i < AXE_MAX; i++)
	{
		if (!_axe[i]) continue;

		_axe[i]->Update();

		// 画面外に出たら削除する
		bool isOutOfScreen = _axe[i]->GetPos().x < 0 || _axe[i]->GetPos().x > SCREEN_WIDTH;
		bool isTouchEnemy = false;
		if (_enemy) {
			isTouchEnemy = _axe[i]->GetColRect().IsCollision(_enemy->GetColRect());
		}
		if (isOutOfScreen || isTouchEnemy)
		{
			DeleteAxe(i);
		}
		if (isTouchEnemy) {
			delete _enemy;
			_enemy = nullptr;
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