#pragma once
#include "Vector2.h"
class Player;

class Stage
{
public:
	Stage(Player* player);
	~Stage();
	void Update();
	void DrawBackGround();
	int GetScrollX();
	int GetScrollY();
private:
	Vector2 pos;
	Vector2 size;
	Player* _player;
};

