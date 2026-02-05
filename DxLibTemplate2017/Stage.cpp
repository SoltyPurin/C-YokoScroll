#include "Stage.h"
#include "Obstacle.h"
#include "Player.h"
#include <DxLib.h>

int _backGroundHandler = 0;
namespace
{
	constexpr float MAP_WIDTH = 5000.0f;	 // マップ全体の幅
	constexpr float MAP_HEIGHT = 1080.0f;	 // マップ全体の高さ
	constexpr float SCREEN_WIDTH = 640.0f;	 // スクリーンの幅
	constexpr float SCREEN_HEIGHT = 480.0f; // スクリーンの高さ
}
int _bgWidth = static_cast<int>(SCREEN_WIDTH)-1;
int _bgHeight = static_cast<int>(SCREEN_HEIGHT)-1;
Stage::Stage(Player* player):
	_player(player)
{
	pos = { 0,0 };
	_backGroundHandler = LoadGraph("Image/BackGround.jpg");
}
Stage::~Stage() {
	DeleteGraph(_backGroundHandler);
}

void Stage::Update() {
	DrawBackGround();
}

void Stage::DrawBackGround() {
	GetGraphSize(_backGroundHandler,&_bgWidth , &_bgHeight);
	int scrollBg = GetScrollX() % _bgWidth;
	DrawExtendGraph(scrollBg, 0, scrollBg+SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, _backGroundHandler, TRUE);
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