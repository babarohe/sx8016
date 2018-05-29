#pragma once
#include "Bus.h"
#include "ram.h"

#define R0 0x00
#define R1 0x01
#define R2 0x02
#define R3 0x03
#define AX 0x04
#define BX 0x05
#define CX 0x06
#define DX 0x07
#define BP 0x0B
#define SP 0x0C
#define FR 0x0D
#define ZZ 0x0E
#define PC 0x0F
#define REGISTER_NUM 16

#define INSTRUCTION_SIZE 3

#define NOT_USE_BUS			0x00
#define USE_BUS_RAM_READ	0x11
#define USE_BUS_RAM_WRITE	0x12
#define USE_BUS_IO_READ		0x21
#define USE_BUS_IO_WRITE	0x22


class SX8016 {
public:
	SX8016(Bus *arg_bus, Ram64k *ram);
	void clock();
	void reset();

	void cpuCtrl();

	void fetch();
	void decode();
	void execute();
	void wbReg();
	void wbMem();

	void setBusMode(int mode);


	unsigned __int16 getRegister(int reg_id);

private:
	// register
	unsigned __int16 reg[REGISTER_NUM];
	Bus *bus;
	Ram64k *ram;
	
	
	unsigned __int64 f_d_bus[INSTRUCTION_SIZE];

	
};

