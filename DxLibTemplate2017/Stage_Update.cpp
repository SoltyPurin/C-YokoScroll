#include "Precompile.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "Jump.h"
#include "PlayerInputManager.h"
#include "ThrowAxe.h"
#include "ThrowKnife.h"
#include "VerticalMoveFloor.h"
#include "Spring.h"
#include "SoundPlayer.h"
#include "AxeEnemy.h"
#include "Skate.h"
#include "Stone.h"
#include "SkatePlayer.h"

Stage::Stage(SoundPlayer* sound): 
	_soundPlayer(sound),
	_graphChipNumX(0),
	_graphChipNumY(0),
	_goal(nullptr)
{
	_player = new Player(_playerInitPos.x, _playerInitPos.y,ShareClass::_playerImage);
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

bool Stage::Update() {
	bool isClear = false;
	//Updateによる計算処理
		for (auto i = _moveFloors.begin(); i != _moveFloors.end();i++) {
		if (*i) {
			(*i)->Update();
		}
		}
		for (auto i = _springs.begin(); i != _springs.end(); i++) {
			if (*i) {
				(*i)->Update();
			}
		}
		for (auto i = _skates.begin(); i != _skates.end(); i++) {
			if (*i) {
				(*i)->Update();
			}
		}
		for (auto i = _stones.begin(); i != _stones.end(); i++) {
			if (*i) {
				(*i)->Update();
			}
		}
		//敵のUpdate
		for (auto i = _enemys.begin(); i != _enemys.end(); ) {
			if (*i) {
				(*i)->Update();
				i++;
			}
			else {
				i = _enemys.erase(i);
			}
		}
		Rect chipRect;
		_inputManager->Update();
		_player->CheckHitMap(chipRect);
		_player->Update();
		//敵の当たり判定の処理
		for (auto i = _enemys.begin(); i != _enemys.end(); ) {
			if (*i) {
				//敵本体の当たり判定ではなく、仮のワールド座標を生成し、敵の座標をそれに変換し渡す
				Rect worldEnemyRect;
				worldEnemyRect.m_left = (*i)->GetColRect().GetLeft() + GetScrollX();
				worldEnemyRect.m_right = (*i)->GetColRect().GetRight() + GetScrollX();
				worldEnemyRect.m_top = (*i)->GetColRect().GetTop() + GetScrollY();
				worldEnemyRect.m_bottom = (*i)->GetColRect().GetBottom() + GetScrollY();
				Rect tempChipRect;
				if (IsCollision(worldEnemyRect, tempChipRect)) {
					(*i)->CheckHitMap(tempChipRect);
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
		return isClear;
	}

	if (DetectPlayerToSkateCollision()) {
		SwitchPlayerState(true,_player->GetPos());
	}

	return isClear;
}

void Stage::SwitchPlayerState(bool isSkatePlayer,Vector2 pos) {
	if (isSkatePlayer) {
		_isSkateing = true;
		delete _player;
		_player = new SkatePlayer(pos.x, pos.y,ShareClass::_playerImage);
		_player->SetStagePointer(this);
		_player->SetAudioPointer(_soundPlayer);
		_player->SetJumpAddres(_jump);
		_inputManager->ResetPointer(_player);

		for (auto& enemy : _enemys) {
			// AxeEnemy 以外の敵もいる可能性があるため、必ず NULL チェック
			AxeEnemy* axeEnemy = dynamic_cast<AxeEnemy*>(enemy.get());
			if (axeEnemy != nullptr) {
				axeEnemy->SetPlayerInfo(_player);
			}
		}

	}
	else {
		_isSkateing = false;
		delete _player;
		_player = new Player(pos.x, pos.y, ShareClass::_playerImage);
		_player->SetStagePointer(this);
		_player->SetAudioPointer(_soundPlayer);
		_player->SetJumpAddres(_jump);
		_inputManager->ResetPointer(_player);


		for (auto& enemy : _enemys) {
			// AxeEnemy 以外の敵もいる可能性があるため、必ず NULL チェック
			AxeEnemy* axeEnemy = dynamic_cast<AxeEnemy*>(enemy.get());
			if (axeEnemy != nullptr) {
				axeEnemy->SetPlayerInfo(_player);
			}
		}

	}
}


void Stage::PlayerFallCheck() {
	if (_player->GetPos().y >= _groundY) {
		_isResetting = true;
	}
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
	SwitchPlayerState(false,Vector2(_playerInitPos.x,_playerInitPos.y));
	_player->ResetPosition();
	_soundPlayer->PlayGameBGM(1);
	LoadMap();
}


int Stage::GetScrollX() {
	int result = static_cast<int>(_player->GetPos().x - SCREEN_WIDTH * 0.3f);
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
	int result = static_cast<int>(_player->GetPos().y - SCREEN_HEIGHT /** 0.6f*/);
	if (result < 0) {
		result = 0;
	}
	if (result > MAP_HEIGHT - SCREEN_HEIGHT) {
		result = MAP_HEIGHT - SCREEN_HEIGHT;
	}

	return result;
}