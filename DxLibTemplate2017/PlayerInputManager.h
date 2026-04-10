#pragma once
class Player;
class PlayerInputManager
{
public:
	PlayerInputManager(Player* player);
	~PlayerInputManager();
	void Update();
	void ResetPointer(Player* player) { _player = player; }
private:
	Player* _player;
	char _keyState[256];
	bool _isRight = true;
	float _moveValue = 5;
};

