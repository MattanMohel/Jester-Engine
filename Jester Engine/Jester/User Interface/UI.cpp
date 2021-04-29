#include "UI.h"
#include "Gui.h"

#include "../Core/Gameobject.h"
#include "../Core/Vector2.h"

#define NORM_WIDTH 0.25f

void Jester::UI::RenderVector2(const std::string& label, Vector2& value, float resetValue = 0.0f)
{
	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);

	ImGui::Text(label.c_str());
	ImGui::SetColumnWidth(0, .3 * width); 
	ImGui::NextColumn();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 3));

	ImGui::PushStyleColor       (ImGuiCol_Button, ImVec4(247 / 255.0f, 184 / 255.0f, 1 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(254 / 255.0f, 199 / 255.0f, 1 / 255.0f, 1.0f));
	ImGui::PushStyleColor (ImGuiCol_ButtonActive, ImVec4(254 / 255.0f, 142 / 255.0f, 1 / 255.0f, 1.0f));
	if (ImGui::Button("X", ImVec2(20, 20)))
		value.x = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::PushItemWidth(.30 * width);
	ImGui::DragFloat("##X", &value.x, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor       (ImGuiCol_Button, ImVec4(234 / 255.0f, 115 / 255.0f, 23 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(234 / 255.0f, 143 / 255.0f, 23 / 255.0f, 1.0f));
	ImGui::PushStyleColor (ImGuiCol_ButtonActive, ImVec4(234 / 255.0f, 105 / 255.0f, 23 / 255.0f, 1.0f));
	if (ImGui::Button("Y", ImVec2(20, 20)))
		value.y = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth()); 
	ImGui::DragFloat("##Y", &value.y, 0.1f, 0.0f, 0.0f, "%.2f"); 
	ImGui::PopItemWidth();
	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID(); 
}

void Jester::UI::RenderFloat(const std::string& label, float& value, bool indent = true)
{
	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());
	ImGui::DragFloat("##X", &value, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	
	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}

void Jester::UI::RenderBool(const std::string& label, bool& value, bool indent = true)
{
	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());
	ImGui::Checkbox("##X", &value);
	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}

void Jester::UI::RenderInt(const std::string& label, int& value, bool indent = true)
{
	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());
	ImGui::DragInt("##X", &value, 0.1f, 0.0f, 0.0f, "%.0f");
	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}

void Jester::UI::RenderComponent(Component* component)
{
	ImGui::PushID(component->GetName());

	RenderBool("Enabled", component->isEnabled, false);

	ImGui::SameLine();

	if (ImGui::CollapsingHeader(component->GetName()))
	{
		ImGui::Separator();
		component->OnGuiUpdate();
	}

	ImGui::Separator();

	ImGui::PopID();
}

void Jester::UI::RenderGameobject(Gameobject* gameobject)
{
	if (gameobject == nullptr) return;

	ImGui::Begin(gameobject->name.c_str());
	{
		RenderBool("Enabled", gameobject->isEnabled, false);

		ImGui::SameLine();

		if (ImGui::CollapsingHeader("Transform"))
		{
			RenderVector2("Positon: ", gameobject->transform.position);
			RenderVector2("Scale: ", gameobject->transform.scale, 1.0f);
			RenderFloat("Rotation: ", gameobject->transform.rotation);
		}

		ImGui::Separator();

		for (auto* component : gameobject->GetComponents())
			RenderComponent(component);
	}

	ImGui::End();
}

void Jester::UI::RenderHierarchy()
{
	static Gameobject* currObj = nullptr;

	ImGui::Begin("Hierarchy");
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

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