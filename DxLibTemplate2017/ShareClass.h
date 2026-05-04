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
    //コンストラクタとデストラクタで確保と解放をやるとうまく動かなかったため専用の関数を用意した
    /// <summary>
    /// プレイヤーの画像を確保する
    /// </summary>
    static void GetImages();
    /// <summary>
    /// プレイヤーの画像を解放する
    /// </summary>
    static void ReleaseImages();
	static float ConstValue;
    static PlayerImages _playerImage;
    static Buttons _buttons;
};

