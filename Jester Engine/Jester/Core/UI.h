#pragma once

#include "../vendors/imgui/imgui.h"
#include "../vendors/imgui/imgui_impl_glfw.h"
#include "../vendors/imgui/imgui_impl_opengl3.h"

#define MAKE_UNIQUE(obj, index) (#obj + std::to_string(index)).c_str()

class Gameobject;

class UIContext  
{
public:
	static void Init();
	static void NewFrame();
	static void RenderFrame();
	static void ShutDown();
	static void RenderGameobject(Gameobject*);
	static void RenderHierarchy();

	static ImGuiIO* io; 
};



