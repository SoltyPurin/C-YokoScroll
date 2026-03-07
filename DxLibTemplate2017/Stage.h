#pragma once
#include "Vector2.h"
#include "Rect.h"
class Player;
class Enemy;
class Axe;
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
	void DetectPlayerToEnemyCollision();
	void DeleteAxe(int index);
	void ResetGame();
	void PlayerFallCheck();
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	Enemy* _enemy;
	Axe* _axe[16];
	float _groundY = 900;
	int _mapData;
	int _mapChipHandle;
	int _graphChipNumX;
	int _graphChipNumY;
};

