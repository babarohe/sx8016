#include "Bus.h"

Bus::Bus() {
	reset();
}

void Bus::reset() {
	// Address bus
	addr_bus = 0;

	// Data bus
	data_bus = 0;

	// Control bus
	ctrl_merq = 0;
	ctrl_iorq = 0;
	ctrl_wr = 0;
	ctrl_rd = 0;

	// CPU control
	in_int = 0;
	in_wait = 0;
	out_halt = 0;
	in_reset = 0;

	// Bus control
	out_busrq = 0;
	in_busak = 0;
}