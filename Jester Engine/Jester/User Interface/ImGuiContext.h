#pragma once

class Object;

class UIContext
{
public:
	static void Init();
	static void NewFrame();
	static void RenderFrame();
	static void ShutDown();
};



