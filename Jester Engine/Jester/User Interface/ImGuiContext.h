#pragma once

#define MAKE_UNIQUE(obj, index) (#obj + std::to_string(index)).c_str()

class Gameobject;

class UIContext
{
public:
	static void Init();
	static void NewFrame();
	static void RenderFrame();
	static void ShutDown();
};



