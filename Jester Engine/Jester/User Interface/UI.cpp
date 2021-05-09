#include "UI.h"
#include "Gui.h"

#include "../Core/Gameobject.h"
#include "../Core/Vector2.h"

template<> bool Jester::UI::Serialize<std::string>(const std::string& label, std::string& value, bool indent)
{
	bool changed = false;

	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());

	//static char buffer[1024] = { *value.c_str() };
	//if (ImGui::InputText(label.c_str(), buffer, IM_ARRAYSIZE(buffer)))
	//	changed = true;

	//value = buffer;

	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

template<> bool Jester::UI::Serialize(const std::string& label, Vector2& value, bool indent)
{
	bool changed = false;

	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);

	ImGui::Text(label.c_str());
	ImGui::SetColumnWidth(0, .3 * width);
	ImGui::NextColumn();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 3));

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(247 / 255.0f, 184 / 255.0f, 1 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(254 / 255.0f, 199 / 255.0f, 1 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(254 / 255.0f, 142 / 255.0f, 1 / 255.0f, 1.0f));
	if (ImGui::Button("X", ImVec2(20, 20)))
	{
		value.x = 0.0f;
		changed = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::PushItemWidth(.30 * width);

	if (ImGui::DragFloat("##X", &value.x, 0.1f, 0.0f, 0.0f, "%.2f"))
		changed = true;

	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(234 / 255.0f, 115 / 255.0f, 23 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(234 / 255.0f, 143 / 255.0f, 23 / 255.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(234 / 255.0f, 105 / 255.0f, 23 / 255.0f, 1.0f));
	if (ImGui::Button("Y", ImVec2(20, 20)))
	{
		value.y = 0.0f;
		changed = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();

	if (ImGui::DragFloat("##Y", &value.y, 0.1f, 0.0f, 0.0f, "%.2f"))
		changed = true;

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

template<> bool Jester::UI::Serialize(const std::string& label, float& value, bool indent)
{
	bool changed = false;

	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());

	if (ImGui::DragFloat("##X", &value, 0.1f, 0.0f, 0.0f, "%.2f"))
		changed = true;

	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

template<> bool Jester::UI::Serialize<Color>(const std::string& label, Color& value, bool indent)
{
	bool changed = false;

	ImGui::Text(label.c_str());
	ImGui::SameLine();
	ImGui::PushID(label.c_str());

	if (ImGui::ColorEdit4("##color", value.GetValuePointer()))
		changed = true;

	ImGui::PopID();

	return changed;
}

template<> bool Jester::UI::Serialize(const std::string& label, int& value, bool indent)
{
	bool changed = false;

	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());
	
	if (ImGui::DragInt("##X", &value, 0.1f, 0.0f, 0.0f, "%.0f"))
		changed = true;

	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

template<> bool Jester::UI::Serialize(const std::string& label, bool& value, bool indent)
{
	bool changed = false;

	float width = ImGui::GetWindowWidth();
	ImGui::PushID(label.c_str());

	if (indent)
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(.3 * width, 3));

	ImGui::Text(label.c_str());

	ImGui::SameLine();
	ImGui::PushItemWidth(ImGui::CalcItemWidth());
	
	if (ImGui::Checkbox("##X", &value))
		changed = true;

	ImGui::PopItemWidth();

	if (indent)
		ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();

	return changed;
}

void Jester::UI::RenderComponent(Component* component)
{
	ImGui::PushID(component->GetName());

	Serialize("Enabled", component->isEnabled, false);

	ImGui::SameLine();

	if (ImGui::CollapsingHeader(component->GetName()))
	{
		ImGui::Separator();
		component->OnGuiUpdate();
	}

	ImGui::Separator();

	ImGui::PopID();
}

void Jester::UI::RenderGameobject(Object* gameobject)
{
	if (gameobject == nullptr) return;

	ImGui::Begin(gameobject->name.c_str());
	{
		Serialize("Enabled", gameobject->isEnabled, false);

		ImGui::SameLine();

		if (ImGui::CollapsingHeader("Transform"))
		{
			Serialize("Positon: ", gameobject->transform.position, true);
			Serialize("Scale: ", gameobject->transform.scale, true);
			Serialize("Rotation: ", gameobject->transform.rotation, true);
		}

		ImGui::Separator();

		for (auto* component : gameobject->GetComponents())
			RenderComponent(component);
	}

	ImGui::End();
}

void Jester::UI::RenderHierarchy()
{
	static Object* currObj = nullptr;

	ImGui::Begin("Hierarchy");
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		for (auto* gameobject : Application::Get()->GetGameobjects())
		{
			ImGui::PushID(gameobject->GetID());
			if (ImGui::Button(gameobject->name.c_str()))
				currObj = gameobject;
			ImGui::PopID();
		}
	}
	ImGui::End();

	RenderGameobject(currObj);
}