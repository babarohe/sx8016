#pragma once
#include "Bus.h"
#define MAX_RAM_SIZE 0xFFFF

class Ram64k {
public:
	Ram64k(Bus *arg_bus, int ram_size);
	~Ram64k();

	void clock();
	void reset();


private:
	unsigned __int8 *data;
	int size;
	Bus *bus;

	void run();
};

