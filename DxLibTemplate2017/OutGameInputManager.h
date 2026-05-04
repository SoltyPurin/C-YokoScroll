#pragma once
#include "ShareClass.h";
class Button;
class ShareClass;
class OutGameInputManager
{
public:
	OutGameInputManager(Buttons buttons);
	~OutGameInputManager();
	/// <summary>
	/// タイトル画面の入力処理
	/// </summary>
	void TitleInput();
	/// <summary>
	/// クリア画面の入力処理
	/// </summary>
	void ResultInput();

private:
	//現在選択しているボタンの番号、0がスタート,1が終了
	int _titleSelectingValue = 0;
	int _resultSelectingValue = 0;
	char _currentKeyState[256];
	char _prevKeyState[256];
	Button* _gameStartButton;
	Button* _exitButton;
	Button* _returnTitleButton;
};

