// ClockGenerator.cpp
#include "ClockGenerator.h"




void ClockGenerator::initClock() {
	/*
	* クロック初期化
	*/
	// 開始時刻兼高精度補正用カウンター
	QueryPerformanceCounter(&init_host_counter);


}

void ClockGenerator::generateClock(int freq) {
	LARGE_INTEGER host_freq;
	LARGE_INTEGER host_counter;

	// 開始取得
	QueryPerformanceCounter(&host_counter);

	unsigned __int64 start_count = host_counter.QuadPart;

	// 処理にかかった時間を計測
	__int64 processed_count = start_count - init_host_counter.QuadPart;
	if (!correction || processed_count < 0) {
		processed_count = 0;
	}

	// ホストCPU周波数取得
	QueryPerformanceFrequency(&host_freq);

	// ホストCPU周波数 / セットしたい周波数
	unsigned __int64 wait_time = host_freq.QuadPart / freq;

	while (1) {
		// 開始時からの差分
		QueryPerformanceCounter(&host_counter);
		unsigned __int64 end_count = host_counter.QuadPart;

		if (wait_time - processed_count <= end_count - start_count) {
			break;
		}

	}


	return;
}


void ClockGenerator::setCorrectionClock(bool val) {
	correction = val;
}


void ClockGenerator::confirmClock() {
	/*
	* クロックを確定
	*/
	LARGE_INTEGER cycle_end_counter;
	LARGE_INTEGER host_freq;

	QueryPerformanceCounter(&cycle_end_counter);
	QueryPerformanceFrequency(&host_freq);

	unsigned __int64 diff_c =  host_freq.QuadPart / (double)(cycle_end_counter.QuadPart - init_host_counter.QuadPart);

	double_clock = diff_c;
	int64_clock = diff_c;

}

double ClockGenerator::getDoubleClock() {

	return double_clock;
}

unsigned __int64 ClockGenerator::getInt64Clock() {

	return int64_clock;
}