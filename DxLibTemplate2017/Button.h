#pragma once
#include "DxLib.h"
#include "Vector2.h"
enum class ButtonJob {
	LoadGameScene,
	GameExit,
	ReturnTitle,
};

class Button
{
public:
	Button(ButtonJob job, int buttonImageHandle, int selectButtonHandle, CHAR* message, Vector2 pos);
	~Button();
	bool IsTouch(Vector2 mousePos);
	void DrawButton();
	void ControllTap();
	void SwitchButtonColor(bool isSelecting);
	void Reset();
private:
	ButtonJob _job;
	int _buttonHandle;
	int _selectButtonHandle;
	int _useButtonHandle;
	CHAR* _message;
	Vector2 _startPos;
	Vector2 _endPos;
	int _xScale = 500;
	int _yScale = 100;
	int _fontHandle;
	Vector2 _textPos;
	bool _isControllSelecting = false;
	enum ButtonState {
		None,
		Selected,
	};

	ButtonState _curState = ButtonState::None;
};

