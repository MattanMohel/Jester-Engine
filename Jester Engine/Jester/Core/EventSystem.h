#pragma once

#include "Jester.h"

//make events trigger on/before application->Run
//OnDestroy: add OnDestroy event to Application

template<typename Args>
struct EventArgs
{
	EventArgs(Args args, Gameobject* sender)
		: args(args), sender(sender)
	{}

	Args args;
	Gameobject* sender;
};

template<typename Args>
class Event
{
	typedef void(*FUNC)(EventArgs<Args>);

public:
	void Invoke(EventArgs<Args> eventArgs)
	{
		for (const FUNC& func : m_Funcs)
		{
			func(eventArgs);
		}
	}
	void operator+= (const FUNC& func)
	{
		m_Funcs.push_back(func);
	}
	void operator-= (const FUNC& func)
	{
		auto it = std::find(m_Funcs.begin(), m_Funcs.end(), func);
		m_Funcs.erase(it);
	}
	void operator = (const FUNC& func)
	{
		m_Funcs.clear();
		m_Funcs.push_back(func);
	}

	void operator! ()
	{
		m_Funcs.clear();
	}

private:
	std::vector<FUNC> m_Funcs;
};

class EmptyEvent 
{
	typedef void(*FUNC)();

public:
	void Invoke()
	{
		for (const FUNC& func : m_Funcs)
		{
			func();
		}
	}
	void operator+= (const FUNC& func)
	{
		m_Funcs.push_back(func);
	}
	void operator-= (const FUNC& func)
	{
		auto it = std::find(m_Funcs.begin(), m_Funcs.end(), func);
		m_Funcs.erase(it);
	}
	void operator = (const FUNC& func)
	{
		m_Funcs.clear();
		m_Funcs.push_back(func);
	}

	void operator! ()
	{
		m_Funcs.clear();
	}

private:
	std::vector<FUNC> m_Funcs;
};



