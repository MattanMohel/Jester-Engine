#pragma once

#include "../Jester.h"
#include "Gui.h"

namespace Jester::UI
{
	void RenderHierarchy();

	template<typename T> bool Serialize(const std::string& label, T& value, bool indent = true)
	{
		static_assert(false, "Value not serializable");
	}
	template<> bool Serialize<std::string>(const std::string&, std::string&, bool);
	template<> bool Serialize<Vector2>(const std::string&, Vector2&, bool);
	template<> bool Serialize<float>(const std::string&, float&, bool);
	template<> bool Serialize<Color>(const std::string&, Color&, bool); 
	template<> bool Serialize<bool>(const std::string&, bool&, bool);
	template<> bool Serialize<int>(const std::string&, int&, bool);

	template<typename T> bool SerializeVec(const std::string& label, std::vector<T>& values, const std::string& itemPreface = "item")
	{
		bool changed = false;

		ImGui::Text(label.c_str());
		for (size_t index = 0; index < values.size(); index++)
		{
			if (Serialize(itemPreface + " " + std::to_string(index), values[index], false))
				changed = true; 
		}

		if (ImGui::Button("Add")) values.push_back(T());
		ImGui::SameLine();
		if (ImGui::Button("Remove") && values.size() != 0) values.erase(values.begin() + values.size() - 1);

		return changed; 
	}

	void RenderGameobject(Object*); 
	void RenderComponent(Component*);
}