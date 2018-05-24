#pragma once
#include "Bus.h"
#define MAX_RAM_SIZE 0xFFFF

class ROM {
public:
	ROM(Bus *arg_bus, int ram_size);
	~ROM();

	void clock();
	void reset();


private:
	unsigned __int8 *data;
	int size;
	Bus *bus;

	void run();
};

