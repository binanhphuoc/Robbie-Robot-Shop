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

Order::Order(int _order_number, time_t _date, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model, int _status) : order_number{_order_number}, date{_date}, price{_price}, sales_associate{_sales_associate}, customer{_customer}, robot_model{_robot_model}, status{_status} {}

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

int Order::get_status()
{
	return status;
}

void Order::set_status(int i)
{
	status = i;
}
