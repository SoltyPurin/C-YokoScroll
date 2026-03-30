#pragma once
#include <vector>
#include "Vector2.h"
#include "Rect.h"
#include "Goal.h"
class Player;
class Enemy;
class Axe;
class ThrowKnife;
class VerticalMoveFloor;
class Spring;
class Goal;
class SoundPlayer;
class Stage
{
public:
	Stage(Player* player,SoundPlayer* sound);
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
	bool DetectPlayerToGoalCollision();
	void ResetGame();
	void PlayerFallCheck();
	void DrawCurrentWeapon();
	void SpawnEnemy(int enIndex, float x, float y);
	void SetMoveFloor(float x, float y);
	void SetSpring(float x, float y);
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	SoundPlayer* _soundPlayer;
	std::vector<Enemy*> _enemys;
	std::vector<VerticalMoveFloor*> _moveFloors;
	std::vector<Spring*> _springs;
	Goal* _goal;
	Axe* _axe[16];
	Axe* _enemyAxe[16];
	ThrowKnife* _knife[16];
	float _groundY = 900;
	int _mapData;
	int _mapChipHandle;
	int _graphChipNumX;
	int _graphChipNumY;
	int _axeHandle;
	int _knifeHandle;
	int _colChipIndex;
	bool _isResetting = false;
};

