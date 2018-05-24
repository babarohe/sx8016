#include "Util.h"

using namespace std;

void monitor(ClockGenerator *clock) {

	double accumulation_clock = 0.0;
	int i = 0;

	__int64 accumulation_clock_i64 = 0;

	LARGE_INTEGER freq;


	while (1) {

		if (!isinf(clock->getDoubleClock()) && clock->getDoubleClock() != 0.0) {
			accumulation_clock += clock->getDoubleClock();
			accumulation_clock_i64 += clock->getInt64Clock();
			Sleep(10);
			i++;
		}


		if (i == 10) {
			// ToDo: SSE
			double avr_clock = accumulation_clock / (double)i;
			__int64 avr_clock_i64 = accumulation_clock_i64 / i;
			int remainder = 0;

			if (!isinf(avr_clock)) {
				QueryPerformanceFrequency(&freq);
				printf("[Clock] Host CPU: %I64dMHz / SX8016 MPU: ", freq.QuadPart / 1000);

				double unit_clock = avr_clock;
				__int64 unit_clock_i64 = avr_clock_i64;
				string unit = "Hz";

				if (avr_clock > 1000000) {
					unit_clock = avr_clock / 1000000.0;
					unit_clock_i64 = avr_clock_i64 / 1000000;
					remainder = 1000000 % unit_clock_i64;
					unit = "MHz";

				}
				else if (avr_clock > 1000) {
					unit_clock = avr_clock / 1000.0;
					unit_clock_i64 = avr_clock_i64 / 1000;
					remainder = 1000 % unit_clock_i64;
					unit = "KHz";

				}
				double show_clock = unit_clock_i64;
				show_clock += remainder / 1000;

				cout << fixed << setprecision(2) << unit_clock << unit << "\r";
				//cout << unit_clock_i64 << '.' << remainder << unit << "\r";
				//cout << fixed << setprecision(2) << show_clock << unit << "\r";
			}

			accumulation_clock = 0.0;
			accumulation_clock_i64 = 0;
			i = 0;
		}
	}
}


void getSystemInformation() {
	OSVERSIONINFOEX OSver;
	ULONGLONG condition = 0;
	OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	OSver.dwMajorVersion = 6;
	OSver.dwMinorVersion = 1;
	VER_SET_CONDITION(condition, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(condition, VER_MINORVERSION, VER_GREATER_EQUAL);

	if (VerifyVersionInfo(&OSver, VER_MAJORVERSION | VER_MINORVERSION, condition))
	{
		// Windows 7ˆÈ~
		//cout << VER_MAJORVERSION << '.' << VER_MINORVERSION << " Build" << OSver.dwBuildNumber;

	}
	else {
		cout << "unsupported operating sys tem." << endl;
	}

	//int REG_edx, REG_ecx, REG_eax;
	//_asm {
	//	mov eax, 1;
	//	cupid ;
	//	mov REG_edx, edx;
	//	mov REG_ecx, ecx;
	//}


#ifdef _AMD64_
	cout << "SX8016 Emulator (x64)" << endl;
#else
	BOOL bWow64Process = FALSE;
	::IsWow64Process(::GetCurrentProcess(), &bWow64Process);
	if (bWow64Process)
	{
		cout << "SX8016 Emulator" << "Host Processor Information x86, Wow64, x86_64 supported processor" << endl;
	}
	else
	{
		cout << "SX8016 Emulator (x86)" << endl;
	}
#endif

	int cpu_info[4];
	int function_id = 0;
	__cpuid(cpu_info, function_id);


}