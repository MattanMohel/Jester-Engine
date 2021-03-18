#pragma once

#include <iostream>

class Logger
{
public:

	enum LogFlag
	{
		Debug,
		Info,
		Warning,
		Error
	};

	template<typename... Args>
	static void Print(const LogFlag& flag, const Args&... args)
	{
		switch (flag)
		{
		case LogFlag::Debug:
			std::cout << "Debug ";
			break;
		case LogFlag::Info:
			std::cout << "Info ";
			break;
		case LogFlag::Warning:
			std::cout << "Warning ";
			break;
		case LogFlag::Error:
			std::cout << "Error ";
			break;
		}

		(std::cout << ... << args) << '\n';
	}

	template<typename... Args>
	static void Print(const Args&... args)
	{

		(std::cout << ... << args) << '\n';
	}

private:
	
};


