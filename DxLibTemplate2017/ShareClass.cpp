#include "Precompile.h"
#include "ShareClass.h"
#include "Button.h"
float ShareClass::ConstValue = 0.016f;

PlayerImages ShareClass::_playerImage;
Buttons ShareClass::_buttons;

ShareClass::ShareClass() {
}
ShareClass::~ShareClass() {

}

void ShareClass::SetButtons(Button* start, Button* exit, Button* returnTitle) {
	_buttons._gameStartButton = start;
	_buttons._exitButton = exit;
	_buttons._returnTitleButton = returnTitle;
}

void ShareClass::GetImages() {
	_playerImage._idle = LoadGraph("Image/Player/PlayerIdle.png");
	_playerImage._jump = LoadGraph("Image/Player/PlayerJump.png");
	_playerImage._throw = LoadGraph("Image/Player/PlayerThrow.png");
	_playerImage._move1 = LoadGraph("Image/Player/PlayerMove1.png");
	_playerImage._move2 = LoadGraph("Image/Player/PlayerMove2.png");

	_playerImage._skateRide = LoadGraph("Image/Player/SkateBoardMoveing.png");
	_playerImage._skateBrake = LoadGraph("Image/Player/SkateBoardStopping.png");
	_playerImage._blowAway = LoadGraph("Image/Player/PlayerBlowAway.png");
}

void ShareClass::ReleaseImages() {
	DeleteGraph(_playerImage._idle);
	DeleteGraph(_playerImage._jump);
	DeleteGraph(_playerImage._move1);
	DeleteGraph(_playerImage._move2);
	DeleteGraph(_playerImage._throw);

	DeleteGraph(_playerImage._skateBrake);
	DeleteGraph(_playerImage._skateRide);

	DeleteGraph(_playerImage._blowAway);
}