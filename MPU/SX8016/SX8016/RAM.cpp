#include "RAM.h"


Ram64k::Ram64k(Bus *arg_bus, int ram_size) {
	bus = arg_bus;
	size = ram_size;

	data = (unsigned __int8 *)malloc(sizeof(__int8) * size);

	if (data == NULL) {
		std::cout << "Memory becomes insufficient." << std::endl;
		throw "Memory becomes insufficient.";
	}
	
	reset();

	//std::thread thread(&Ram64k::clock, this);

}


Ram64k::~Ram64k() {
	free(data);
}

void Ram64k::run() {
	while (1) {
		clock();

	}

}

void Ram64k::clock() {
	if (bus->ctrl_merq) {
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

void Ram64k::reset() {
	for (int i = 0; i < size; i++) {
		data[i] = 0x00;
	}

}
