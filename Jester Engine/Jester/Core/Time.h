#pragma once

#include <ctime>
#include <chrono>

class Application;

class Time
{

#define MIL 1000.0

	friend class Application;

	typedef std::chrono::high_resolution_clock CLOCK;

public:

	void Init()
	{
		m_InitPoint = m_PreviousTime = CLOCK::now();
	}
	void OnUpdate()
	{ 
		m_DeltaTime = CLOCK::now() - m_PreviousTime;
		m_PreviousTime = CLOCK::now();

		fpsTracker = m_DeltaTime.count();
	}

	double DeltaTime() const
	{
		return (double) m_DeltaTime.count();
	}
	double TimeSinceStartupInSeconds() const
	{
		return 
			std::chrono::duration_cast<std::chrono::milliseconds>(CLOCK::now() - m_InitPoint).count() / MIL;
	}	
	double TimeSinceStartupInMilliseconds() const
	{
		return 
			std::chrono::duration_cast<std::chrono::milliseconds>(CLOCK::now() - m_InitPoint).count();
	}
	static void PrintDateTime()
	{
		time_t now = time(0);
		tm* time = localtime(&now);

		std::string tm_sec  = time->tm_sec  < 10 ? "0" + std::to_string(time->tm_sec )  : std::to_string(time->tm_sec);
		std::string tm_min  = time->tm_min  < 10 ? "0" + std::to_string(time->tm_min )  : std::to_string(time->tm_min);
		std::string tm_hour = time->tm_hour < 10 ? "0" + std::to_string(time->tm_hour) : std::to_string(time->tm_hour);

		std::cout << "[" + tm_hour + ':' + tm_min + ':' + tm_sec + "] ";
	}

	double GetFPS() const
	{
		return round(1 / fpsTracker);
	}

private:

	static Time* Get()
	{
		static Time* s_Instance = new Time();
		return s_Instance;
	}

	Time() : fpsTracker{ 0 } {}
	~Time() { delete Get(); }

	double fpsTracker;

	std::chrono::duration<double> m_DeltaTime;
	std::chrono::time_point<CLOCK> m_InitPoint;
	std::chrono::time_point<CLOCK> m_PreviousTime;
}; 