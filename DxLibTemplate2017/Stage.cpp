#include "Stage.h"
#include "Obstacle.h"
#include "Player.h"
#include <DxLib.h>

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
	constexpr int CHIP_DATA[CHIP_NUM_Y][CHIP_NUM_X] =
	{
		{3, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 1, 1},
		{3, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 1, 1, 1},
		{3, 0, 0, 1, 2, 2, 2},
		{3, 1, 1, 2, 2, 2, 2},
		{3, 2, 2, 2, 2, 2, 2}
	};
}
int _bgWidth = static_cast<int>(SCREEN_WIDTH)-1;
int _bgHeight = static_cast<int>(SCREEN_HEIGHT)-1;
Stage::Stage(Player* player,Obstacle* obstacle):
	_player(player),
	_graphChipNumX(0),
	_graphChipNumY(0)
{
	pos = { 0,0 };
	_backGroundHandler = LoadGraph("Image/BackGround.jpg");
	_mapHandle = LoadGraph("Image/mapChip.png");

	int graphW = 0;
	int graphH = 0;
	GetGraphSize(_mapHandle, &graphW, &graphH);

	_graphChipNumX = graphW / CHIP_SIZE;
	_graphChipNumY = graphH / CHIP_SIZE;
}
Stage::~Stage() {
	DeleteGraph(_backGroundHandler);
	DeleteGraph(_mapHandle);
}

void Stage::Update() {
	DrawBackGround();
	DrawMapChip();
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
				_mapHandle, true);


#ifdef _DEBUG
			// 当たり判定
			DrawBoxAA(posX, posY, posX + CHIP_SIZE * kChipScale, posY + CHIP_SIZE * kChipScale, 0x00ff00, false);
#endif
		}
	}
}

bool Stage::IsCollision(Rect rect, Rect& chipRect)
{
	for (int y = 0; y < CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < CHIP_NUM_X; x++)
		{
			// マップチップ0番は当たり判定がないため飛ばす
			if (CHIP_DATA[y][x] == 0) continue;

			int chipLeft = static_cast<int>(x * CHIP_SIZE * kChipScale);
			int chipRight = static_cast<int>(chipLeft + CHIP_SIZE * kChipScale);
			int chipTop = static_cast<int>(y * CHIP_SIZE * kChipScale);
			int chipBottom = static_cast<int>(chipTop + CHIP_SIZE * kChipScale);

			// 絶対に当たらない場合
			if (chipLeft > rect.GetRight()) continue;
			if (chipTop > rect.GetBottom()) continue;
			if (chipRight < rect.GetLeft()) continue;
			if (chipBottom < rect.GetTop()) continue;

			// ぶつかったマップチップの矩形を設定する
			chipRect.m_left = static_cast<float>(chipLeft);
			chipRect.m_right = static_cast<float>(chipRight);
			chipRect.m_top = static_cast<float>(chipTop);
			chipRect.m_bottom = static_cast<float>(chipBottom);

			// いずれかのチップに当たっていたら終了する
			return true;
		}
	}

	return false;
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