#include "ShareClass.h"
#include "DxLib.h"
float ShareClass::KoteiValue = 0.016f;

NormalPlayerImages ShareClass::_normalImage;
SkatePlayerImages ShareClass::_skateImage;

ShareClass::ShareClass() {
}
ShareClass::~ShareClass() {

}

void ShareClass::GetImages() {
	_normalImage._idle = LoadGraph("Image/Player/PlayerIdle.png");
	_normalImage._jump = LoadGraph("Image/Player/PlayerJump.png");
	_normalImage._throw = LoadGraph("Image/Player/PlayerThrow.png");
	_normalImage._move1 = LoadGraph("Image/Player/PlayerMove1.png");
	_normalImage._move2 = LoadGraph("Image/Player/PlayerMove2.png");

	_skateImage._ride = LoadGraph("Image/Player/SkateBoardMoveing.png");
	_skateImage._brake = LoadGraph("Image/Player/SkateBoardStopping.png");
}

void ShareClass::ReleaseImages() {
	DeleteGraph(_normalImage._idle);
	DeleteGraph(_normalImage._jump);
	DeleteGraph(_normalImage._move1);
	DeleteGraph(_normalImage._move2);
	DeleteGraph(_normalImage._throw);

	DeleteGraph(_skateImage._brake);
	DeleteGraph(_skateImage._ride);
}