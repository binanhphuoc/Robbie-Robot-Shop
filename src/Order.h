#ifndef ORDER_H
#define ORDER_H

#include "Sales_associate.h"
#include "Customer.h"
#include <string>
#include <ctime>
#include "Robot_model.h"
#include "State.h"

using namespace std;
/*
struct Date
{
	int month;
	int day;
	int year;
};
*/
struct Price
{
	double subtotal;
	double shipping;
	double tax = 8.25/100;
/*
public:
	Price(double _subtotal, double _shipping, double _tax) : subtotal(_subtotal), shipping(_shipping), tax(_tax) {}
	double get_subtotal() {return subtotal;}
	double get_shipping() {return shipping;}
	double get_tax() {return tax;}
	double get_total() {return subtotal + shipping + tax;}*/
};

class Order
{
	int order_number;
	/*Date date;*/
	time_t date;
	Price price;
	Sales_associate* sales_associate;
	Customer* customer;
	Robot_model* robot_model;
	State_order state;
	
public:

	Order(int _order_number, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model/*, int _status*/);
	Order(int _order_number, time_t _date, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model, State_order s);
	int get_order_number();
	Price get_price();
	string get_date();
	time_t get_date_time_t() {return date;}
	Sales_associate* get_sales_associate();
	Robot_model* get_robot_model();
	Customer* get_customer();
	
	state_enum get_state(int path);
	string get_state_string(int path);
	void set_state(state_enum s1, state_enum s2);
	void next_state(int path, event e);
};

#endif
