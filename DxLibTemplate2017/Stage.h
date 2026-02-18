#pragma once
#include "Vector2.h"
#include "Rect.h"
class Player;
class Obstacle;

class Stage
{
public:
	Stage(Player* player,Obstacle* obstacle);
	~Stage();
	void LoadMap();
	void Update();
	void DrawBackGround();
	void DrawMapChip();
	int GetScrollX();
	int GetScrollY();
	bool IsCollision(Rect rect, Rect& chipRect);
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
	int _mapData;
	int _backGroundHandle;
	int _graphChipNumX;
	int _graphChipNumY;
};

