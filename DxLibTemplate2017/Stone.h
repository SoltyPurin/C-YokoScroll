#pragma once
#include "Rect.h"
#include "Vector2.h"
class Stage;
class Stone
{
public:
	Stone(int stoneHandle,Stage* stagePointer, Vector2 pos);
	~Stone();
	void Update();
	void Draw(float scrrolX, float scrrolY);
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }

private:
	Rect _collisionRect;
	Vector2 _currentPos;
	Stage* _stagePointer;
	int _stoneHandle;
	int _scale = 80;
};

