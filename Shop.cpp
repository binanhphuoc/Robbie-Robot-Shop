#include "Shop.h"
#include "Robot_part.h"
#include "Robot_model.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

/////////////////////////////////////////
//////		ROBOT PARTS
/////////////////////////////////////////

void Shop::create_new_robot_part(part_t p, string name, int model_number, double cost, double weight, string description, string image_filename, double var1, double var2)
{	
	if (p == HEAD)
	{
		robot_parts.push_back(new Head(name, model_number, cost, weight, description, image_filename, var1));
	}
	if (p == ARM)
	{
		robot_parts.push_back(new Arm(name, model_number, cost, weight, description, image_filename, var1));
	}
	if (p == LOCOMOTOR)
	{
		robot_parts.push_back(new Locomotor(name, model_number, cost, weight, description, image_filename, var1, var2));
	}
	if (p == BATTERY)
	{
		robot_parts.push_back(new Battery(name, model_number, cost, weight, description, image_filename, var1));
	}
	if (p == TORSO)
	{
		robot_parts.push_back(new Torso(name, model_number, cost, weight, description, image_filename, var1/*,var2*/));
	}
	
}

int Shop::remove_robot_part(int i)
{
	if (i >= robot_parts.size() || i < 0)
	{
		return 1;
	}
	
	remove_robot_model_contains_part(i);
	delete robot_parts.at(i);
	robot_parts.erase(robot_parts.begin()+i);
	return 0;
}

Robot_part* Shop::get_part(int i)
{
	return robot_parts.at(i);
}

Robot_part* Shop::get_part(part_t p, int i)
{	
	int j, index = -1;
	for (j = 0; j < robot_parts.size(); j++)
	{
		if (robot_parts.at(j)->get_part() == p)
		{
			index++;
			if (index == i)
				return robot_parts.at(j);
		}
	}
	return NULL;
}

int Shop::get_part_size()
{
	return robot_parts.size();
}

int Shop::get_part_size(part_t p)
{
	int count = 0;
	for (int i = 0; i < get_part_size(); i++)
	{
		if (get_part(i)->get_part() == p)
			count++;
	}
	return count;
}

bool Shop::foundPart(Robot_part* part)
{
	for (int i = 0; i < get_part_size(); i++)
	{
		if (part == get_part(i))
			return true;
	}
	return false;
}

int Shop::findPart(Robot_part* rp)
{
	for (int i = 0; i < get_part_size(); i++)
	{
		if (rp == get_part(i))
			return i;
	}
}

void Shop::save_part(ofstream& ost)
{
	int size = get_part_size();
	ost << size << endl;
	for (int i = 0; i < size; i++)
	{
		get_part(i)->save(ost);
	}
}

void Shop::load_part(ifstream& ist)
{
	int size; string str;
	int j; part_t p;
	ist >> size; getline(ist, str);
	//cout << "Part size: " << size << endl;
	for (int i = 0; i < size; i++)
	{
		ist >> j; getline(ist, str);
		p = (part_t) j;
		if (p == ARM)
			robot_parts.push_back(new Arm(ist));
		else if (p == HEAD)
			robot_parts.push_back(new Head(ist));
		else if (p == LOCOMOTOR)
			robot_parts.push_back(new Locomotor(ist));
		else if (p == BATTERY)
			robot_parts.push_back(new Battery(ist));
		else if (p == TORSO)
			robot_parts.push_back(new Torso(ist));
	}
}

/////////////////
/////------------------------End ROBOT PARTS--------------------------
/////////////////


//////////////////////////////////////////
///////		ROBOT MODELS
//////////////////////////////////////////

void Shop::create_new_robot_model(string name, int model_number, double price, vector<Robot_part*> parts)
{
	Robot_model* model = new Robot_model(name, model_number, price);
	for (Robot_part* p : parts)
	{
		if (p->get_part() == TORSO)
			model->attach_torso(p);
		else if (p->get_part() == HEAD)
			model->attach_head(p);
		else if (p->get_part() == LOCOMOTOR)
			model->attach_locomotor(p);
		else if (p->get_part() == ARM)
			model->attach_arm(p);
		else if (p->get_part() == BATTERY)
			model->attach_battery(p);
	}
	robot_models.push_back(model);
}

Robot_model* Shop::get_model(int i)
{
	return robot_models.at(i);
}

int Shop::get_model_size()
{
	return robot_models.size();
}

int Shop::remove_robot_model(int i)
{
	if (i >= robot_models.size() || i < 0)
	{
		return 1;
	}
	
	delete robot_models.at(i);
	robot_models.erase(robot_models.begin()+i);
	return 0;
}

int Shop::remove_robot_model_contains_part(int i)
{
	if (i < 0 || i >= robot_parts.size())
		return 1;	
	Robot_part* rp = robot_parts.at(i);
	for (int j = 0; j < robot_models.size(); j++)
	{
		Robot_model* rm = robot_models.at(j);
		if (rp->get_part() == ARM)
		{
			for (int arm = 0; arm < 2; arm++)
			{
				if (rm->get_part(ARM, arm) == rp)
				{
					//cout << "same location" << endl;
					remove_robot_model(j);
					break;
				}
			}
		}
		else if (rp->get_part() == BATTERY)
		{
			for (int bat = 0; bat < rm->get_part(LOCOMOTOR)->get_battery_compartments(); bat++)
			{
				if (rm->get_part(BATTERY, bat) == rp)
				{
					//cout << "same location" << endl;
					remove_robot_model(j);
					break;
				}
			}
		}
		else if (rm->get_part(rp->get_part()) == rp)
		{
			//cout << "same location" << endl;
			remove_robot_model(j);
		}
	}
	return 0;
}

int Shop::findModel(Robot_model* rm)
{
	for (int i = 0; i < get_model_size(); i++)
	{
		if (rm == get_model(i))
			return i;
	}
}

void Shop::save_model(ofstream& ost)
{
	int size = get_model_size();
	ost << size << endl;
	for (int i = 0; i < size; i++)
	{
		Robot_model* rm = robot_models.at(i);
		vector<int> var;
		var.push_back(findPart(rm->get_torso()));
		var.push_back(findPart(rm->get_head()));
		var.push_back(findPart(rm->get_locomotor()));
		var.push_back(findPart(rm->get_arm(0)));
		var.push_back(findPart(rm->get_arm(1)));
		for (int j = 0; j < rm->get_torso()->get_battery_compartments(); j++)
			var.push_back(findPart(rm->get_battery(j)));
		rm->save(ost, var);
	}
}

void Shop::load_model(ifstream& ist)
{
	string str; int size;
	ist >> size; getline(ist, str);
	for (int i =0; i< size; i++)
	{
		string name;
		getline(ist, name);
		
		int model_number;
		ist >> model_number; getline(ist, str);
		
		double price;
		ist >> price; getline(ist, str);
		
		vector<Robot_part*> rp;
		for (int j = 0; j < 5; j++)
		{
			int part_number;
			ist >> part_number;getline(ist, str);
			rp.push_back(robot_parts.at(part_number));
		}
		
		int battery_compartments = rp.at(0)->get_battery_compartments();
		for (int j = 0; j < battery_compartments; j++)
		{
			int part_number;
			ist >> part_number;getline(ist, str);
			rp.push_back(robot_parts.at(part_number));
		}
	
		create_new_robot_model(name, model_number, price, rp);
		
	}
}

/////////////////
/////-------------------------End ROBOT MODELS------------------------
/////////////////

/////////////////
/////	CUSTOMER
/////////////////

void Shop::create_new_customer(string name, int customer_number, string phone_number, string email_address)
{
	customers.push_back(new Customer(name, customer_number, phone_number, email_address));
}

Customer* Shop::get_customer(int i)
{
	return customers.at(i);
}

int Shop::get_customer_size()
{
	return customers.size();
}

int Shop::remove_customer(int i)
{
	if (i < 0 || i >= customers.size())
		return 1;
	delete customers.at(i);
	customers.erase(customers.begin()+i);
	return 0;
}

int Shop::findBC(Customer* c)
{
	for (int i = 0; i< customers.size(); i++)
	{
		if (c == customers.at(i))
			return i;
	}
}

void Shop::save_customer(ofstream& ost)
{
	int size = get_customer_size();
	ost << size << endl;
	for (int i = 0; i < size; i++)
	{
		Customer* c = customers.at(i);
		ost << c->get_name() << endl;
		ost << c->get_customer_number() << endl;
		ost << c->get_phone_number() << endl;
		ost << c->get_email_address() << endl;	
	}
}

void Shop::load_customer(ifstream& ist)
{
	string str; int size;
	ist >> size; getline(ist, str);
	for (int i =0; i< size; i++)
	{
		string name;
		getline(ist, name);
		
		int customer_number;
		ist >> customer_number; getline(ist, str);
		
		string phone_number;
		getline(ist, phone_number);
		
		string email_address;
		getline(ist, email_address);
	
		create_new_customer(name, customer_number, phone_number, email_address);
		
	}
}

/////////////////
/////------------------------End CUSTOMER------------------------------
/////////////////

/////////////////
/////	SALES ASSOCIATE
/////////////////

void Shop::create_new_sales_associate(string name, int employee_number)
{
	sales_associates.push_back(new Sales_associate(name, employee_number));
}

Sales_associate* Shop::get_sales_associate(int i)
{
	return sales_associates.at(i);
}

int Shop::get_sales_associate_size()
{
	return sales_associates.size();
}

int Shop::remove_sales_associate(int i)
{
	if (i < 0 || i >= sales_associates.size())
		return 1;
	delete sales_associates.at(i);
	sales_associates.erase(sales_associates.begin()+i);
	return 0;
}

int Shop::findSA(Sales_associate* sa)
{
	for (int i = 0; i< sales_associates.size(); i++)
	{
		if (sa == sales_associates.at(i))
			return i;
	}
}

void Shop::save_sales_associate(ofstream& ost)
{
	int size = get_sales_associate_size();
	ost << size << endl;
	for (int i = 0; i < size; i++)
	{
		Sales_associate* c = sales_associates.at(i);
		ost << c->get_name() << endl;
		ost << c->get_employee_number() << endl;	
	}
}

void Shop::load_sales_associate(ifstream& ist)
{
	string str; int size;
	ist >> size; getline(ist, str);
	for (int i =0; i< size; i++)
	{
		string name;
		getline(ist, name);
		
		int employee_number;
		ist >> employee_number; getline(ist, str);
		
		create_new_sales_associate(name, employee_number);
	}
}

/////////////////
/////------------------------End SALES ASSOCIATE------------------------------
/////////////////


/////////////////
//////		ORDER
/////////////////

void Shop::create_new_order(int order_number,Robot_model* rm,Price price,Sales_associate* sa,Customer* c)
{
	Order* order = new Order(order_number, price, sa, c, rm);
	orders.push_back(order);
}

void Shop::create_new_order(int order_number, time_t date, Robot_model* rm,Price price,Sales_associate* sa,Customer* c, int status)
{
	Order* order = new Order(order_number, date, price, sa, c, rm, status);
	orders.push_back(order);
}

Order* Shop::get_order(int i)
{
	return orders.at(i);
}

int Shop::get_order_size()
{
	return orders.size();
}

int Shop::remove_order(int i)
{
	if (i < 0 || i >= orders.size())
		return 1;
	delete orders.at(i);
	orders.erase(orders.begin()+i);
	return 0;
}

void Shop::save_order(ofstream& ost)
{
	int size = get_order_size();
	ost << size << endl;
	for (int i = 0; i < size; i++)
	{
		Order* c = orders.at(i);
		ost << c->get_order_number() << endl;
		ost << c->get_date_time_t() << endl;
		ost << c->get_price().subtotal << endl;
		ost << c->get_price().shipping << endl;
		ost << c->get_price().tax << endl;
		ost << findSA(c->get_sales_associate()) << endl;
		ost << findBC(c->get_customer()) << endl;
		ost << findModel(c->get_robot_model()) << endl;
		ost << c->get_status() << endl;
	}
}

void Shop::load_order(ifstream& ist)
{
	string str; int size;
	ist >> size; getline(ist, str);
	for (int i =0; i< size; i++)
	{
		int order_number;
		ist >> order_number; getline(ist, str);
		
		time_t date;
		ist >> date; getline(ist, str);
		
		Price price;
		ist >> price.subtotal; getline(ist, str);
		ist >> price.shipping; getline(ist, str);
		ist >> price.tax; getline(ist, str);
		
		int j;
		ist >> j; getline(ist, str);
		Sales_associate* sa = sales_associates.at(j);
		
		ist >> j; getline(ist, str);
		Customer* bc = customers.at(j);
		
		ist >> j; getline(ist, str);
		Robot_model* rm = robot_models.at(j);

		int status;
		ist >> status; getline(ist,str);		
		
		create_new_order(order_number, date, rm, price, sa, bc, status);
	}
}

/////////////////
///-------------------------End ORDER---------------------------
/////////////////
