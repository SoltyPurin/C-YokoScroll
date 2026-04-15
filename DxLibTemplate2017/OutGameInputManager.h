#pragma once
#include "ShareClass.h";
class Button;
class ShareClass;
class OutGameInputManager
{
public:
	OutGameInputManager(Buttons buttons);
	~OutGameInputManager();
	void TitleInput();
	void ResultInput();

private:
	//現在選択しているボタンの番号、0がスタート,1が終了
	int _titleSelectingValue = 0;
	int _resultSelectingValue = 0;
	char _keyState[256];
	Button* _gameStartButton;
	Button* _exitButton;
	Button* _returnTitleButton;
};

