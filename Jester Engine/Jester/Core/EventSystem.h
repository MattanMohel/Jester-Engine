#pragma once

class Object;

template<typename Args>
struct EventArgs
{
	EventArgs(Args args, Object* sender)
		: args(args), sender(sender)
	{}

	Args args;
	Object* sender;
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




