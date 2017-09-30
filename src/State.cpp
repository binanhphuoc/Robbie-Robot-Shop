#include "State.h"

void State::handle(event e, int path)
{
	if (path == 1 && e == BEGIN && s == PENDING)
	{
		s = PACKAGING;
		return;
	}
	if (e == PACKAGED && s == PACKAGING)
	{
		s = SHIPPING;
		return;
	}
	if (e == SHIPPED && s == SHIPPING)
	{
		s = COMPLETED;
		return;
	}
	if (path == 2 && e == BEGIN && s == PENDING)
	{
		s = BILLING;
		return;
	}
	if (e == BILLED && s == BILLING)
	{
		s = COMPLETED;
		return;
	}
	if (e == PAID && s == ACCEPTING)
	{
		s = COMPLETED;
		return;
	}
	if (e == CANCEL && (s == ACCEPTING || s == SHIPPING))
	{
		s = CANCELED;
		return;
	}
}

//--------------------------------------------------------

void State_order::handle(int path, event e)
{
	if (path == 1)
	{
		s1.handle(e, 1);
		if (s1.get_state() == CANCELED)
			canceled = true;
	}
	if (path == 2)
	{
		s2.handle(e, 2);
		if (s2.get_state() == CANCELED)
			canceled = true;
	}
}

state_enum State_order::get_state(int path)
{
	if (canceled)
		return CANCELED;	
	if (path == 1)
		return s1.get_state();
	if (path == 2)
		return s2.get_state();
}

void State_order::set(int path, state_enum s)
{
	if (path == 1)
		s1.set(s);
	if (path == 2)
		s2.set(s);
}


