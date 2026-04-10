#pragma once
#include <vector>
#include "Vector2.h"
#include "Rect.h"
#include "Goal.h"
class Player;
class Jump;
class Enemy;
class Axe;
class ThrowKnife;
class VerticalMoveFloor;
class Spring;
class Goal;
class Skate;
class SoundPlayer;
class PlayerInputManager;
class Stone;
class Stage
{
public:
	Stage(SoundPlayer* sound);
	~Stage();
	void LoadMap();
	bool Update();
	void Draw();
	void DrawBackGround();
	void DrawMapChip();
	int GetScrollX();
	int GetScrollY();
	bool IsCollision(Rect rect, Rect& chipRect);
	void DrawAxe();
	void UpdateAxe();
	void DeleteAxe(int index);
	void DrawEnemyAxe();
	void UpdateEnemyAxe();
	void DeleteEnemyAxe(int index);
	void DrawKnife();
	void UpdateKnife();
	void DeleteKnife(int index);
	void DetectPlayerToEnemyCollision();
	void DetectPlayerToObstacleCollision();
	bool DetectPlayerToSkateCollision();
	bool DetectPlayerToGoalCollision();
	void ResetGame();
	void PlayerFallCheck();
	void DrawCurrentWeapon();
	void SpawnEnemy(int enIndex, float x, float y);
	void SetMoveFloor(float x, float y);
	void SetSpring(float x, float y);
	void SetSkate(float x, float y);
	void SetFellStone(float x, float y);
	void SwitchPlayerState(bool isSkatePlayer,Vector2 pos);
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	Jump* _jump;
	SoundPlayer* _soundPlayer;
	PlayerInputManager* _inputManager;
	std::vector<Enemy*> _enemys;
	std::vector<VerticalMoveFloor*> _moveFloors;
	std::vector<Spring*> _springs;
	std::vector<Skate*> _skates;
	std::vector<Stone*> _stones;
	Goal* _goal;
	Axe* _axe[3];
	Axe* _enemyAxe[16];
	ThrowKnife* _knife[3];
	float _groundY = 900;
	int _mapData;
	int _mapChipHandle;
	int _graphChipNumX;
	int _graphChipNumY;
	int _axeHandle;
	int _knifeHandle;
	int _skateHandle;
	int _colChipIndex;
	int _rideSkateIndex;
	int _brakeSkateIndex;
	int _stoneHandle;
	bool _isResetting = false;
	bool _isSkateing = false;
};

