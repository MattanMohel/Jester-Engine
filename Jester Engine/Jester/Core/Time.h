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

		static size_t fpsIndex = 0;
		fpsTracker[fpsIndex] = m_DeltaTime.count();
		fpsIndex = (fpsIndex + 1) % FPS_RESOLUTION;
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

	size_t GetFPS() const
	{
		double total = 0;
		for (size_t i = 0; i < FPS_RESOLUTION; i += 5)
		{
			total += fpsTracker[i + 0];
			total += fpsTracker[i + 1];
			total += fpsTracker[i + 2];
			total += fpsTracker[i + 3];
			total += fpsTracker[i + 4];
		}

		return round(FPS_RESOLUTION / total);
	}

private:

	static Time* Get()
	{
		static Time* s_Instance = new Time();
		return s_Instance;
	}

	Time() : fpsTracker{ 0 } {}
	~Time() { delete Get(); }

	static constexpr size_t FPS_RESOLUTION = 5;
	static_assert(FPS_RESOLUTION % 5 == 0, "FPS_RESOLUTION must be divisible by 5");

	double fpsTracker[FPS_RESOLUTION];

	std::chrono::duration<double> m_DeltaTime;
	std::chrono::time_point<CLOCK> m_InitPoint;
	std::chrono::time_point<CLOCK> m_PreviousTime;
}; 