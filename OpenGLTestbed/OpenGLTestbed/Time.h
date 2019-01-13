#pragma once
#include <chrono>
class Time 
{
private:
	static std::chrono::steady_clock::time_point startTime;
public:
	static void ResetTime() { startTime = std::chrono::steady_clock::now(); }

	static float GetTime() { return (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count(); }

};
