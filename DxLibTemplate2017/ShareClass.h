#pragma once
#include "Button.h"
struct PlayerImages {
    int _idle;
    int _move1;
    int _move2;
    int _jump;
    int _throw;
    int _skateRide;
    int _skateBrake;
    int _blowAway;
};

struct Buttons
{
    Button* _gameStartButton;
    Button* _exitButton;
    Button* _returnTitleButton;
};


class ShareClass
{
public:
    ShareClass();
    ~ShareClass();
    static void SetButtons(Button* start, Button* exit, Button* returnTitle);
    static void GetImages();
    static void ReleaseImages();
	static float ConstValue;
    static PlayerImages _playerImage;
    static Buttons _buttons;
};

