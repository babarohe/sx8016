#include "ClockGenerator.h"
#include "SX8016.h"
#include "RAM.h"
#include "Util.h"

const char AA[] = R"(/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
/_      _____________  ___ ______ _______  _______  _______       /_
/_     /   _____/\   \/  //  __  \\   _  \ \   _  \ \   _  \      /_
/_     \_____  \  \     / >      </  /_\  \/  /_\  \/  /_\  \     /_
/_     /        \ /     \/   --   \  \_/   \  \_/   \  \_/   \    /_
/_    /_______  //___/\  \______  /\_____  /\_____  /\_____  /    /_
/_            \/       \_/      \/       \/       \/       \/     /_
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
/_ Y a m a m o o  M P U  E m u l a t o r  X  S e r i e s  8 0 1 6 /_
/_                                                                /_
/_        C O P Y R I G H T  S . Y A M A M U R A  2018.           /_
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
)";

using namespace std;


int main()
{
	cout << AA << endl;

	

	ClockGenerator *clock = new ClockGenerator();
	clock->setCorrectionClock(false);

	Bus *bus = new Bus();
	Ram64k *ram = new Ram64k(bus, MAX_RAM_SIZE);
	SX8016 *sx8k = new SX8016(bus);

	auto mon = thread(monitor, clock);

	Sleep(20);

	while (1) {
		clock->initClock();

		sx8k->clock();

		//cout << sx8k->getRegister(PC) << endl;

		clock->generateClock(10000);
		clock->confirmClock();

	}

	
	// memory release
	delete(clock);
	delete(bus);
	delete(sx8k);


    return 0;
}


