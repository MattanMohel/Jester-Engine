#pragma once

#include <iostream>
#include <csignal>

#include "Time.h"

enum class LogFlag
{
	Debug,
	Info,
	Warning,
	Error
};

class Logger
{
public:
	template<typename... Args>
	inline static void Print(const LogFlag& flag, const Args&... args)
	{

		Time::PrintDateTime();

		switch (flag)
		{
		case LogFlag::Debug:
			std::cout << "-DEBUG- ";
			break;
		case LogFlag::Info:
			std::cout << "-INFO- ";
			break;
		case LogFlag::Warning:
			std::cout << "-WARNING- ";
			break;
		case LogFlag::Error:
			std::cout << "-ERROR- ";
			break;
		}

		(std::cout << ... << args) << '\n';

		if (flag == LogFlag::Error)
			std::raise(SIGINT);

	}

	template<typename... Args>
	inline static void Print(const Args&... args)
	{
		Time::PrintDateTime();

		(std::cout << ... << args) << '\n';
	}
	
};


