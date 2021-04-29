#include "ImGuiContext.h"

#include "Gui.h"

#include "../Core/Window.h"

void UIContext::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(Window::Get()->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UIContext::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIContext::RenderFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIContext::ShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

