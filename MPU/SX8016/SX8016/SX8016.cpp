#include "SX8016.h"



SX8016::SX8016(Bus *arg_bus, Ram64k *ram) {
	this->bus = arg_bus;
	this->ram = ram;
	reset();
}

void SX8016::clock() {
	cpuCtrl();


	wbMem();
	wbReg();
	execute();
	decode();
	fetch();

}



void SX8016::reset() {
	// Init registor
	for (int i = 0; i < REGISTER_NUM; i++) {
		reg[i] = 0;
	}


}


void SX8016::fetch() {
	// RAMŽg—p
	setBusMode(USE_BUS_IO_READ);

	for (int i = 0; i < INSTRUCTION_SIZE; i++) {
		bus->addr_bus = (unsigned __int16)(reg[PC] + i);
		ram->clock();
		f_d_bus[i] = bus->data_bus;
	}

	std::cout << "addr-> " << bus->addr_bus << std::endl;
	std::cout << "data-> " << (int)bus->data_bus << std::endl;


	reg[PC] += INSTRUCTION_SIZE;

}

void SX8016::decode() {

}

void SX8016::execute() {

}

void SX8016::wbReg() {

}

void SX8016::wbMem() {

}

void SX8016::cpuCtrl() {

}

void SX8016::setBusMode(int mode) {
	switch (mode) {
	case NOT_USE_BUS:
		bus->ctrl_merq = false;
		bus->ctrl_iorq = false;
		bus->ctrl_rd = false;
		bus->ctrl_wr = false;
		break;
	case USE_BUS_RAM_READ:
		bus->ctrl_merq = true;
		bus->ctrl_iorq = false;
		bus->ctrl_rd = true;
		bus->ctrl_wr = false;
		break;
	case USE_BUS_RAM_WRITE:
		bus->ctrl_merq = true;
		bus->ctrl_iorq = false;
		bus->ctrl_rd = false;
		bus->ctrl_wr = true;
		break;
	case USE_BUS_IO_READ:
		bus->ctrl_merq = false;
		bus->ctrl_iorq = true;
		bus->ctrl_rd = true;
		bus->ctrl_wr = false;
		break;
	case USE_BUS_IO_WRITE:
		bus->ctrl_merq = false;
		bus->ctrl_iorq = true;
		bus->ctrl_rd = false;
		bus->ctrl_wr = true;
		break;
	}

}

unsigned __int16 SX8016::getRegister(int reg_id) {
	return reg[reg_id];
}
