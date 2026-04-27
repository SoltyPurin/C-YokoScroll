#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "Jump.h"
#include "PlayerInputManager.h"
#include "VerticalMoveFloor.h"
#include "ThrowKnife.h"
#include "ThrowAxe.h"
#include "Skate.h"
#include "SoundPlayer.h"
#include "Enemy.h"
#include "AxeEnemy.h"
#include "Goal.h"
#include "Stone.h"
#include "Spring.h"
Stage::Stage(SoundPlayer* sound) :
	_soundPlayer(sound),
	_graphChipNumX(0),
	_graphChipNumY(0),
	_goal(nullptr)
{
	_player = new Player(_playerInitPos.x, _playerInitPos.y, ShareClass::_playerImage);
	_jump = new Jump();
	_player->SetStagePointer(this);
	_player->SetAudioPointer(_soundPlayer);
	_player->SetJumpAddres(_jump);
	_inputManager = new PlayerInputManager(_player);
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
	_stoneHandle = LoadGraph("Image/Stone.png");

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
	DeleteGraph(_rideSkateIndex);
	DeleteGraph(_brakeSkateIndex);
	// その他、new したオブジェクトの解放漏れがないか確認
	delete _player;
	delete _jump;
	delete _inputManager;
	for (int i = 0; i < WEAPON_MAX; i++) {
		DeleteAxe(i);
		DeleteKnife(i);
		DeleteEnemyAxe(i);
	}
	if (_goal != nullptr) {
		_goal.reset();
	}
	_enemys.clear();
	_moveFloors.clear();
	_springs.clear();
	_skates.clear();
	_stones.clear();

}

void Stage::ResetGame() {
	for (int i = 0; i < WEAPON_MAX; i++) {
		DeleteAxe(i);
		DeleteKnife(i);
		DeleteEnemyAxe(i);
	}
	if (_goal != nullptr) {
		_goal.reset();
	}
	_enemys.clear();
	_moveFloors.clear();
	_springs.clear();
	_skates.clear();
	SwitchPlayerState(false, Vector2(_playerInitPos.x, _playerInitPos.y));
	_player->ResetPosition();
	_soundPlayer->PlayGameBGM(1);
	LoadMap();
}
