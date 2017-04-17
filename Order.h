#ifndef ORDER_H
#define ORDER_H

#include "Sales_associate.h"
#include "Customer.h"
#include <string>
#include <ctime>
#include "Robot_model.h"

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
	double tax = 0.15;
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
	int status = 0;
	
	
public:
	Order(int _order_number, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model/*, int _status*/);
	Order(int _order_number, time_t _date, Price _price, Sales_associate* _sales_associate, Customer* _customer, Robot_model* _robot_model, int _status);
	int get_order_number();
	Price get_price();
	string get_date();
	time_t get_date_time_t() {return date;}
	Sales_associate* get_sales_associate();
	Robot_model* get_robot_model();
	Customer* get_customer();
	int get_status();
	void set_status(int i);
};

#endif
