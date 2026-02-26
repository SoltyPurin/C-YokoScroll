#pragma once
#include "Vector2.h"
#include "Rect.h"
class Player;
class ThrowAxe;
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
	void DeleteAxe(int index);
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	ThrowAxe* _axe[16];
	int _mapData;
	int _backGroundHandle;
	int _graphChipNumX;
	int _graphChipNumY;
};

