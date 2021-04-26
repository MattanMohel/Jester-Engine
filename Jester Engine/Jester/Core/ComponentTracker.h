#pragma once

#include <string>
class Gameobject;

//std::string LAST_COMPONENT;
void RetrieveComponent(Gameobject* gameobject, const std::string& componentName);

const std::string GetLastComponent();