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
	useRam();

	for (int i = 0; i < REGISTER_NUM; i++) {
		reg[i] = 0;
	}


}


void SX8016::fetch() {

	for (int i = 0; i < INSTRUCTION_SIZE; i++) {
		bus->addr_bus = (unsigned __int16)(reg[PC] + i);
		ram->clock();
		f_d_bus[i] = bus->data_bus;
	}

	std::cout << bus->addr_bus << std::endl;
	std::cout << bus->data_bus << std::endl;

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

void SX8016::useRam(bool is_write) {
	bus->ctrl_merq = true;
	bus->ctrl_iorq = false;
	
	if (is_write) {
		bus->ctrl_rd = false;
		bus->ctrl_wr = true;

	}
	else {
		bus->ctrl_rd = true;
		bus->ctrl_wr = false;
	}

}

void SX8016::useIO(bool is_write) {
	bus->ctrl_merq = false;
	bus->ctrl_iorq = true;

	if (is_write) {
		bus->ctrl_rd = false;
		bus->ctrl_wr = true;

	}
	else {
		bus->ctrl_rd = true;
		bus->ctrl_wr = false;
	}

}

unsigned __int16 SX8016::getRegister(int reg_id) {
	return reg[reg_id];
}
