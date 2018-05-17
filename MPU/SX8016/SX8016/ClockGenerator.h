#pragma once


using namespace std::chrono;

class ClockGenerator
{
public:
	void initClock();

	void generateClock(int freq);

	void confirmClock();

	double getDoubleClock();
	unsigned __int64 getInt64Clock();

private:
	system_clock::time_point start;
	double double_clock;
	unsigned __int64 int64_clock;


};


