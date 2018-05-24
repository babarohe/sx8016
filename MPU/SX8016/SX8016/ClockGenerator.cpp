// ClockGenerator.cpp
#include "ClockGenerator.h"




void ClockGenerator::initClock() {
	/*
	* �N���b�N������
	*/
	// �J�n�����������x�␳�p�J�E���^�[
	QueryPerformanceCounter(&init_host_counter);


}

void ClockGenerator::generateClock(int freq) {
	LARGE_INTEGER host_freq;
	LARGE_INTEGER host_counter;

	// �J�n�擾
	QueryPerformanceCounter(&host_counter);

	unsigned __int64 start_count = host_counter.QuadPart;

	// �����ɂ����������Ԃ��v��
	__int64 processed_count = start_count - init_host_counter.QuadPart;
	if (!correction || processed_count < 0) {
		processed_count = 0;
	}

	// �z�X�gCPU���g���擾
	QueryPerformanceFrequency(&host_freq);

	// �z�X�gCPU���g�� / �Z�b�g���������g��
	unsigned __int64 wait_time = host_freq.QuadPart / freq;

	while (1) {
		// �J�n������̍���
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
	* �N���b�N���m��
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