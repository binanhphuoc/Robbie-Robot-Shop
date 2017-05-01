#ifndef SHOP_H
#define SHOP_H

#include "Robot_model.h"
#include "Robot_part.h"
#include "Customer.h"
#include "Sales_associate.h"
#include "Order.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Shop
{
	vector<Robot_part*> robot_parts;
	vector<Robot_model*> robot_models;
	vector<Customer*> customers;
	vector<Sales_associate*> sales_associates;
	vector<Order*> orders;
public:
	
	//////	ROBOT PARTS
	void create_new_robot_part(part_t p, string name, int model_number, double cost, double weight, string description, string image_filename, double var1 = 0, double var2 = 0);
	int remove_robot_part(int i);
	Robot_part* get_part(int i);
	Robot_part* get_part(part_t p, int i);
	int get_part_size();
	int get_part_size(part_t p);
	bool foundPart(Robot_part* rp);
	int findPart(Robot_part* rp);
	void save_part(ofstream& ost);
	void load_part(ifstream& ist);
	/////-------End ROBOT PARTS------------------

	///// ROBOT MODELS
	void create_new_robot_model(string name, int model_number, string image_filename, double price, vector<Robot_part*> parts);
	Robot_model* get_model(int i);
	int get_model_size();
	int remove_robot_model(int i);
	int remove_robot_model_contains_part(int i);
	int findModel(Robot_model* rm);
	void save_model(ofstream& ost);
	void load_model(ifstream& ist);
	/////-----------End ROBOT MODELS-------------

	///// CUSTOMERS
	void create_new_customer(string name, int customer_number, string phone_number, string email_address);
	Customer* get_customer(int i);
	int get_customer_size();
	int remove_customer(int i);
	int findBC(Customer* c);
	void save_customer(ofstream& ost);
	void load_customer(ifstream& ist);
	/////------------End CUSTOMERS---------------	

	///// SALES ASSOCIATE
	void create_new_sales_associate(string name, int employee_number);
	Sales_associate* get_sales_associate(int i);
	int get_sales_associate_size();
	int remove_sales_associate(int i);
	int findSA(Sales_associate* sa);
	void save_sales_associate(ofstream& ost);
	void load_sales_associate(ifstream& ist);
	/////------------End SALES ASSOCIATE---------
	
	///// ORDER
	void create_new_order(int order_number,Robot_model* rm,Price price,Sales_associate* sa,Customer* c);
	void create_new_order(int order_number, time_t date, Robot_model* rm,Price price,Sales_associate* sa,Customer* c, int status);
	Order* get_order(int i);
	int get_order_size();
	int remove_order(int i);
	void save_order(ofstream& ost);
	void load_order(ifstream& ist);
	/////------------End ORDER---------
};

#endif
