#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../Core/Log.h"

#include "ComponentTracker.h"

#define PATH "Jester/Core/ComponentTracker.cpp"
#define SCRIPTS_PATH "Jester/Sandbox/"

static void AddComponentToFile(const std::string& componentName)
{
	//std::fstream newFile;
	//newFile.open("Jester/Sandbox/test.h", std::ios::out);

	//if (!newFile)
	//{
	//	Logger::Print("nope");
	//}

	std::string lastComponent = GetLastComponent();
	std::ifstream stream(PATH);
	std::string source, line;

	source += "#include \"";
	source += "../Sandbox/";
	source += componentName; 
	source += ".h\"\n";

	int counter = 1;
	while (getline(stream, line))
	{
		if (line.find("const std::string LAST_COMPONENT = ") != std::string::npos)
		{
			source += "const std::string LAST_COMPONENT = \"";
			source += componentName;
			source += "\";\n";
			continue;
		}

		source += line;
		source += '\n';

		if (counter == 0)
		{
			source += "    else if (componentName == \"";
			source += componentName;
			source += "\")\n";
			source += "        component = gameobject->AddComponent<";
			source += componentName;
			source += ">();\n";

			counter--; 
		}

		if (line.find(lastComponent) != std::string::npos)
			counter--;
	}

	std::ofstream file;
	file.open(PATH);
	file << source; 
	file << "//Test";
	file.close(); 
}