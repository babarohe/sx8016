#include "Util.h"

using namespace std;

void monitor(ClockGenerator *clock) {

	double accumulation_clock = 0.0;
	int i = 0;

	//__int128;

	LARGE_INTEGER freq;

	while (1) {

		if (!isinf(clock->getDoubleClock()) && clock->getDoubleClock() != 0.0) {
			accumulation_clock += clock->getDoubleClock();
			Sleep(10);
			i++;
		}


		if (i == 10) {
			double avr_clock = accumulation_clock / (double)i;


			if (!isinf(avr_clock)) {
				QueryPerformanceFrequency(&freq);
				printf("[Clock] Host CPU: %dMHz / SX8016 MPU: ", freq.LowPart / 1000);

				double unit_clock = avr_clock;
				string unit = "Hz";

				if (avr_clock > 1000000) {
					unit_clock = avr_clock / 1000000.0;
					unit = "MHz";

				}
				else if (avr_clock > 1000) {
					unit_clock = avr_clock / 1000.0;
					unit = "KHz";

				}

				cout << fixed << setprecision(2) << unit_clock << unit << "\r";
			}

			accumulation_clock = 0.0;
			i = 0;
		}
	}
}