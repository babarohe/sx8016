#pragma once
class Bus {
public:
	// Address bus
	unsigned __int16 addr_bus;

	// Data bus
	unsigned __int8  data_bus;

	// Control bus
	unsigned __int8 ctrl_merq;
	unsigned __int8 ctrl_iorq;
	unsigned __int8 ctrl_wr;
	unsigned __int8 ctrl_rd;

	// CPU control
	unsigned __int8  in_int;
	unsigned __int8  in_wait;
	unsigned __int8  out_halt;
	unsigned __int8  in_reset;

	// Bus control
	unsigned __int8 out_busrq;
	unsigned __int8 in_busak;

	Bus();

	void reset();

};