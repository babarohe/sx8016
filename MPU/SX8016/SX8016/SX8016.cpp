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
	// RAM使用
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
	// データ取得
	__int8 instruction_operand = f_d_bus[0];
	__int8 left_operand = f_d_bus[1];
	__int8 right_operand = f_d_bus[2];

	// 命令上位1ビット解釈
	switch (instruction_operand & 0b10000000) {
	case(0b00000000):
		// 8ビット命令
		break;
	case(0b10000000):
		// 16ビット命令
		break;
	}

	// 命令下位2ビット解釈
	switch (instruction_operand & 0b00000011) {
	case (0b00):
		operand_addr = reg[left_operand];
		operand_dest = reg[left_operand];
		operand_src = reg[right_operand];
		break;
	case (0b01):
		operand_addr = reg[left_operand];
		operand_dest = reg[left_operand];
		operand_src = right_operand;
		break;
	case (0b10):
		operand_addr = left_operand;
		operand_dest = left_operand;
		operand_src = reg[right_operand];
		break;
	case (0b11):
		operand_addr = left_operand;
		operand_dest = left_operand;
		operand_src = right_operand;
		break;
	}
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
