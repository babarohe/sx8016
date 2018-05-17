// ClockGenerator.cpp
#include "ClockGenerator.h"




void ClockGenerator::initClock() {
	/*
	* クロック初期化
	*/
	start = system_clock::now();

}

void ClockGenerator::generateClock(int freq) {
	
	//Sleep(1);

	return;
}




void ClockGenerator::confirmClock() {
	/*
	* クロックを確定
	*/
	system_clock::duration diff_time = (system_clock::now() - start);

	try {
		double_clock = 10000000.0 / diff_time.count();
	}
	catch (...){
		double_clock = 0.0;
	}

	try {
		int64_clock = 10000000.0 / diff_time.count();
	}
	catch (...) {
		int64_clock = 0.0;
	}


}

double ClockGenerator::getDoubleClock() {

	return double_clock;
}

unsigned __int64 ClockGenerator::getInt64Clock() {

	return int64_clock;
}