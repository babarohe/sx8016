#pragma once


using namespace std::chrono;

class ClockGenerator
{
public:
	void initClock();

	void generateClock(int freq);

	void confirmClock();

	void setCorrectionClock(bool val);

	double getDoubleClock();
	unsigned __int64 getInt64Clock();

private:
	LARGE_INTEGER init_host_counter;
	double double_clock;
	unsigned __int64 int64_clock;
	bool correction = true;

};


