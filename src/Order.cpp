#include <string>
#include "Order.h"
#include "Customer.h"
#include <ctime>
#include "Sales_associate.h"

using namespace std;

Order::Order(int _order_number,/* Date _date, */Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model/*, int _status*/) : order_number{_order_number},/* date{_date}, */price{_price}, sales_associate{_sales_associate}, customer{_customer}, robot_model{_robot_model}/*, status{_status}*/ 
{
	date = time(0);
}

Order::Order(int _order_number, time_t _date, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model, State_order s) : order_number{_order_number}, date{_date}, price{_price}, sales_associate{_sales_associate}, customer{_customer}, robot_model{_robot_model}, state{s} {}

/*
double Order::robot_cost()
{
	return robot_model.get_price();
}*/

int Order::get_order_number()
{
	return order_number;
}

Price Order::get_price()
{
	return price;
}
	
string Order::get_date()
{
	return string(ctime(&date));
}

Sales_associate* Order::get_sales_associate()
{
	return sales_associate;
}

Robot_model* Order::get_robot_model()
{
	return robot_model;
}

Customer* Order::get_customer()
{
	return customer;
}

state_enum Order::get_state(int path)
{
	return state.get_state(path);
}

void Order::set_state(state_enum s1, state_enum s2)
{
	state.set(1, s1);
	state.set(2, s2);
}

void Order::next_state(int path, event e)
{
	state.handle(path, e);
}

string Order::get_state_string(int path)
{
	switch (get_state(path))
	{
	case PENDING:
		return "Pending";
	case PACKAGING:
		return "Packaging";
	case SHIPPING:
		return "Shipping";
	case BILLING:
		return "Billing";
	case ACCEPTING:
		return "Accepting";
	case COMPLETED:
		return "Completed";
	case CANCELED:
		return "Canceled";
	}
}
