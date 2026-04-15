#include "OutGameInputManager.h"
#include "Pad.h"
#include <DxLib.h>
#include "ShareClass.h"

OutGameInputManager::OutGameInputManager(Buttons buttons):
_gameStartButton(buttons._gameStartButton),
_exitButton(buttons._exitButton),
_returnTitleButton(buttons._returnTitleButton){
	
}

OutGameInputManager::~OutGameInputManager() {

}

void OutGameInputManager::TitleInput() {
	for (int i = 0; i < 256; i++) {
		_prevKeyState[i] = _currentKeyState[i];
	}
	GetHitKeyStateAll(_currentKeyState);
	bool isSpaceTrigger = (_currentKeyState[KEY_INPUT_SPACE] == 1 && _prevKeyState[KEY_INPUT_SPACE] == 0);
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_UP) || _currentKeyState[KEY_INPUT_UP]){
		_titleSelectingValue = 0;
		_gameStartButton->SwitchButtonColor(true);
		_exitButton->SwitchButtonColor(false);
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN) || _currentKeyState[KEY_INPUT_DOWN]) {
		_titleSelectingValue = 1;
		_gameStartButton->SwitchButtonColor(false);
		_exitButton->SwitchButtonColor(true);
	}

	if (Pad::IsTrigger(PAD_INPUT_1) || isSpaceTrigger) {
		switch (_titleSelectingValue)
		{
		case 0:
			_gameStartButton->ControllTap();
			break;
		default:
			_exitButton->ControllTap();
			break;
		}
	}
}


void OutGameInputManager::ResultInput() {
	for (int i = 0; i < 256; i++) {
		_prevKeyState[i] = _currentKeyState[i];
	}
	GetHitKeyStateAll(_currentKeyState);
	bool isSpaceTrigger = (_currentKeyState[KEY_INPUT_SPACE] == 1 && _prevKeyState[KEY_INPUT_SPACE] == 0);
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_UP) || _currentKeyState[KEY_INPUT_UP]) {
		_resultSelectingValue = 0;
		_returnTitleButton->SwitchButtonColor(true);
		_exitButton->SwitchButtonColor(false);
	}
	else if (Pad::IsTrigger(PAD_INPUT_DOWN) || _currentKeyState[KEY_INPUT_DOWN]) {
		_resultSelectingValue = 1;
		_returnTitleButton->SwitchButtonColor(false);
		_exitButton->SwitchButtonColor(true);
	}

	if (Pad::IsPress(PAD_INPUT_1) ||isSpaceTrigger) {
		switch (_resultSelectingValue)
		{
		case 0:
			_returnTitleButton->ControllTap();
			break;
		default:
			_exitButton->ControllTap();
			break;
		}
	}

}