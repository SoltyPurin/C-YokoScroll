#include "Button.h"
#include "DxLib.h"

namespace {
	constexpr int FONT_SIZE = 64;
}

Button::Button(ButtonJob job,int buttonImageHandle,int selectButtonHandle, CHAR* message,Vector2 pos):
_job(job),
_buttonHandle(buttonImageHandle),
_selectButtonHandle(selectButtonHandle),
_message(message),
_startPos(pos)
{
	_useButtonHandle = _buttonHandle;
	_endPos.x = _startPos.x + _xScale;
	_endPos.y = _startPos.y + _yScale;
	_textPos.x = _startPos.x*1.05f;
	_textPos.y = _startPos.y*1.05f;
	_fontHandle = CreateFontToHandle(NULL, FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING);
}

Button::~Button() {

}

bool Button::IsTouch(Vector2 mousePos) 
{
	bool isTouch = false;
	if (mousePos.x >_startPos.x && mousePos.x <_endPos.x &&
		mousePos.y > _startPos.y && mousePos.y < _endPos.y&& (GetMouseInput() & MOUSE_INPUT_LEFT)) {
		isTouch = true;
	}
	if (mousePos.x > _startPos.x && mousePos.x <_endPos.x &&
		mousePos.y > _startPos.y && mousePos.y < _endPos.y ) {
		_useButtonHandle = _selectButtonHandle;
	}
	else {
		_useButtonHandle = _buttonHandle;
	}
	return isTouch;
}

void Button::DrawButton() 
{
	DrawExtendGraph(_startPos.x, _startPos.y, _endPos.x,_endPos.y , _useButtonHandle, TRUE);
	DrawStringFToHandle(_textPos.x, _textPos.y, _message, GetColor(0, 0, 0), _fontHandle);
}