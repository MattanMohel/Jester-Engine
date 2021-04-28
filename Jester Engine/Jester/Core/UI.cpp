#include "UI.h"

#include "Window.h"
#include "Gameobject.h"
#include "Vector2.h"

ImGuiIO* UIContext::io = nullptr;

void UIContext::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;

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

void UIContext::RenderGameobject(Gameobject* gameobject)
{
	if (gameobject == nullptr) return;

	ImGui::Begin(gameobject->name.c_str()); 
	{
		ImGui::Text("Enabled"); ImGui::SameLine(); ImGui::Checkbox("", &gameobject->isEnabled);
		ImGui::InputFloat2("Positon", gameobject->transform.position.GetValuePointer());
		ImGui::InputFloat2("Scale", gameobject->transform.scale.GetValuePointer());
		ImGui::InputFloat("Rotation", &gameobject->transform.rotation);

		size_t i = 0;
		for (auto* component : gameobject->GetComponents())
		{
			ImGui::PushID(MAKE_UNIQUE(component, i));
			ImGui::Checkbox("Enabled", &component->isEnabled);
			component->OnGuiUpdate();
			ImGui::PopID(); i++;
		}
	}

	static bool showNext = false;
	if (ImGui::Button("Add Component"))
		showNext = true;

	if (showNext)
	{
		static char buffer[1024] = "";
		ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer));
		ImGui::SameLine();
		
		if (ImGui::Button("Add") || !ImGui::IsItemFocused)
		{
			showNext = false;
			/*Retrieve Component*/
		}
	}

	ImGui::End();
}

void UIContext::RenderHierarchy()
{
	static Gameobject* currObj = nullptr; 

	ImGui::Begin("Hierarchy");
	{
		for (auto* gameobject : Application::Get()->GetGameobjects())
		{
			if (ImGui::Button(gameobject->name.c_str()))
				currObj = gameobject;
		}

		static bool showNext = false;
		if (ImGui::Button("Create New Component"))
			showNext = true;

		if (showNext)
		{
			static char buffer[1024] = "";
			ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer));
			ImGui::SameLine();

			if (ImGui::Button("Create") || !ImGui::IsItemFocused)
			{
				showNext = false;
				/*Add component*/
			}
		}

	}
	ImGui::End(); 

	RenderGameobject(currObj); 
}