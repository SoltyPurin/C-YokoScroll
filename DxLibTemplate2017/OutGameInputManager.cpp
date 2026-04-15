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
	GetHitKeyStateAll(_keyState);
	if (Pad::IsPress(PAD_INPUT_UP) || _keyState[KEY_INPUT_UP]){
		_titleSelectingValue = 0;
		_gameStartButton->SwitchButtonColor(true);
		_exitButton->SwitchButtonColor(false);
	}
	else if (Pad::IsPress(PAD_INPUT_DOWN) || _keyState[KEY_INPUT_DOWN]) {
		_titleSelectingValue = 1;
		_gameStartButton->SwitchButtonColor(false);
		_exitButton->SwitchButtonColor(true);
	}

	if (Pad::IsPress(PAD_INPUT_1) || _keyState[KEY_INPUT_SPACE]) {
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
	GetHitKeyStateAll(_keyState);
	if (Pad::IsPress(PAD_INPUT_UP) || _keyState[KEY_INPUT_UP]) {
		_resultSelectingValue = 0;
		_returnTitleButton->SwitchButtonColor(true);
		_exitButton->SwitchButtonColor(false);
	}
	else if (Pad::IsPress(PAD_INPUT_DOWN) || _keyState[KEY_INPUT_DOWN]) {
		_resultSelectingValue = 1;
		_returnTitleButton->SwitchButtonColor(false);
		_exitButton->SwitchButtonColor(true);
	}

	if (Pad::IsPress(PAD_INPUT_1) || _keyState[KEY_INPUT_SPACE]) {
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