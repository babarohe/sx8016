#include "ROM.h"

using namespace std;

ROM::ROM(Bus *arg_bus, int rom_size) {
	bus = arg_bus;
	size = rom_size;

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

	ifstream fin;

	fin.open("rom/rom");
	if (!fin) {
		std::cout << "IO Error. failed file open." << std::endl;
		return;
		//throw "IO Error. failed file open.";
	}

	int read_byte = 0;

	while (!fin.eof()) {
		char data_buf;
		fin.read(&data_buf, sizeof(__int8));
		data[read_byte] = data_buf;

		read_byte++;

	}

	fin.close();

	std::string print_buf = "";
	for (int i = 0; i < 65536; i++) {
		if (i % 16 == 0) {
			printf("0x%08X | ", i);
		}

		printf("%02X ", data[i]);

		if (i % 16 == 7) {
			printf(" ");
		}
		if (i % 16 == 15) {
			printf("\n");
		}
		if (i % 512 == 511) {
			printf("-----------+-------------------------------------------------\n");
			printf(" ADDRESS   | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n");
			printf("-----------+-------------------------------------------------\n");
		}
	}
	printf("\n");
}
