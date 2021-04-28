#pragma once

#include "KeySignatures.h"
#include <glm/vec2.hpp>

class GLFWwindow;
class Window; 

#define GLFW_PRESS 1
#define GLFW_RELEASE 0

struct Input
{

	friend Window;

	Input() = delete;

	//Returns true if key is pressed
	static bool GetKey(const KeySig& signature);
	//Returns true on frame key was pressed
	static bool GetKeyDown(const KeySig& signature);
	//Returns true on frame key is released
	static bool GetKeyUp(const KeySig& signature);
	//Returns the latest input
	static KeySig GetKeyInput();
	//Returns if signature represents a character
	static inline bool isChar(const KeySig& signature)
	{
		return (int)signature >= 65 && (int)signature <= 90;
	}
	//Returns if signature represents a number
	static inline bool isNum(const KeySig& signature)
	{
		return ((int)signature >= 48 && (int)signature <= 57) ||
			((int)signature >= 320 && (int)signature <= 329);
	}
	//Returns if signature represents a punctuation mark
	static inline bool isPunc(const KeySig& signature)
	{
		return (int)signature >= 32 && (int)signature <= 47;
	}

	static inline float GetXDelta() { return posDelta.x; }
	static inline float GetYDelta() { return posDelta.y; }

private:
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
	{
		lastInput = (KeySig)key;
		prevKeys[(int)key] = keys[(int)key];
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos)
	{
		if (mouseFirstMoved)
		{
			lastPos = glm::vec2(xPos, yPos);
			mouseFirstMoved = false;
		}

		posDelta.x = (float)xPos - lastPos.x;
		posDelta.y = lastPos.y - (float)yPos;

		lastPos = glm::vec2(xPos, yPos);
	}

	static glm::vec2 posDelta;
	static glm::vec2 lastPos;
	static bool mouseFirstMoved;

	static KeySig lastInput;
	static bool prevKeys[1024];
	static bool keys[1024];
};


