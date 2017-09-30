#ifndef STATE_H
#define STATE_H

#include <stdexcept>
#include <iostream>
#include <fstream>

enum state_enum{PENDING, PACKAGING, SHIPPING, BILLING, ACCEPTING, COMPLETED, CANCELED};

enum event{BEGIN, PACKAGED, SHIPPED, BILLED, PAID, CANCEL};

class State {
public:
	void handle(event e, int path = 0);
	state_enum get_state() {return s;}
	void set(state_enum _s) {s = _s; }
private:
	state_enum s = PENDING;
};

class State_order
{
public:
	void handle(int path, event e);
	state_enum get_state(int path);
	void set(int path, state_enum s);
	bool canceled = false;

private:
	State s1;
	State s2;
};

#endif
