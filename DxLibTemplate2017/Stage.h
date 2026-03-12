#pragma once
#include <vector>
#include "Vector2.h"
#include "Rect.h"
class Player;
class Enemy;
class Axe;
class ThrowKnife;
class VerticalMoveFloor;
class Stage
{
public:
	Stage(Player* player);
	~Stage();
	void LoadMap();
	void Update();
	void DrawBackGround();
	void DrawMapChip();
	int GetScrollX();
	int GetScrollY();
	bool IsCollision(Rect rect, Rect& chipRect);
	void DrawAxe();
	void UpdateAxe();
	void DrawKnife();
	void UpdateKnife();
	void DetectPlayerToEnemyCollision();
	void DetectPlayerToMoveFloorCollision();
	void DeleteAxe(int index);
	void DeleteKnife(int index);
	void ResetGame();
	void PlayerFallCheck();
	void DrawCurrentWeapon();
	void SpawnEnemy(int enIndex, float x, float y);
	void SetMoveFloor(float x, float y);
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	std::vector<Enemy*> _enemys;
	std::vector<VerticalMoveFloor*> _moveFloors;
	Axe* _axe[16];
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

