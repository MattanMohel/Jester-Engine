#include "Input.h"

Vector2 Input::lastPos;
Vector2 Input::posDelta;
bool Input::mouseFirstMoved = true;

KeySig Input::lastInput;
bool Input::prevKeys[1024];
bool Input::keys[1024];

bool Input::GetKey(const KeySig& signature)
{
	return keys[(int)signature] == true;
}

bool Input::GetKeyDown(const KeySig& signature)
{
	if (keys[(int)signature] && !prevKeys[(int)signature])
	{
		prevKeys[(int)signature] = true;
		return true;
	}

	return false;
}

bool Input::GetKeyUp(const KeySig& signature)
{
	if (!keys[(int)signature] && prevKeys[(int)signature])
	{
		prevKeys[(int)signature] = false;
		return true;
	}

	return false;
}

KeySig Input::GetKeyInput()
{
	KeySig input = lastInput;
	lastInput = (KeySig)0;
	return input;
}

