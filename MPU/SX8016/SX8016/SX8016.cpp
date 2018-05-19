#include "SX8016.h"



SX8016::SX8016(Bus *arg_bus) {
	this->bus = arg_bus;

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

	for (int i = 0; i < REGISTER_NUM; i++) {
		registers[i] = 0;
	}


}


void SX8016::fetch() {

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
