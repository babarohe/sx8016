#include "ROM.h"

using namespace std;

ROM::ROM(Bus *arg_bus, int ram_size) {
	bus = arg_bus;
	size = ram_size;

	data = (unsigned __int8 *)malloc(sizeof(__int8) * size);

	if (data == NULL) {
		std::cout << "Memory becomes insufficient." << std::endl;
		throw "Memory becomes insufficient.";
	}
	
	reset();

}


ROM::~ROM() {
	free(data);
}

void ROM::run() {
	while (1) {
		clock();

	}

}

void ROM::clock() {
	if (bus->ctrl_iorq) {
		if (bus->ctrl_rd) {
			// Read
			bus->data_bus = data[bus->addr_bus];

		}
		else if (bus->ctrl_wr) {
			// Write
			data[bus->addr_bus] = bus->data_bus;

		}
	}

}

void ROM::reset() {
	for (int i = 0; i < size; i++) {
		data[i] = 0x00;
	}

	ifstream fin("rom/rom");
	if (!fin) {
		std::cout << "IO Error. failed file open." << std::endl;
		throw "IO Error. failed file open.";

	}

	

}
