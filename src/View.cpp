#include "View.h"
#include "Shop.h"
#include "Robot_part.h"
#include "Robot_model.h"
#include "Customer.h"
#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

using namespace std;

View::View(Shop& sh) : shop(sh) {}

Menu View::main_menu()
{
	Menu menu;
	menu.content = "-----------------------------\n";
	menu.content += "      ROBBIE ROBOT SHOP      \n";
	menu.content += "-----------------------------\n";
	menu.content += "(1) Create new robot part\n";
	menu.content += "(2) List robot parts\n";
	menu.content += "(3) Remove robot part\n";

	menu.content += "\n(4) Create new model\n";	
	menu.content += "(5) List all models\n";
	menu.content += "(6) Remove robot model\n";
	
	menu.content += "\n(7) Create new customer\n";	
	menu.content += "(8) View customer information\n";

	menu.content += "\n(9) Create new sales associate\n";
	menu.content += "(10) List sales associates\n";

	menu.content += "\n(11) Create new order\n";
	menu.content += "(12) View order\n";
	
	menu.content += "\n(0) Exit\n";
	menu.content += "-----------------------------\n\n";
	menu.min = 0;
	menu.max = 12;
	return menu;
}

Menu View::part_menu()
{
	Menu menu;
	menu.content = "-----------------------------\n";
	menu.content += "       ROBOT PART MENU      \n";
	menu.content += "-----------------------------\n";
	menu.content += "(1) Head\n";	
	menu.content += "(2) Arm\n";
	menu.content += "(3) Locomotor\n";
	menu.content += "(4) Battery\n";
	menu.content += "(5) Torso\n";
	menu.content += "\n(0) Cancel\n";
	menu.content += "-----------------------------\n\n";
	menu.min = 0;
	menu.max = 5;
	return menu;
}

Menu View::model_menu()
{
	Menu menu;
	menu.content = "-----------------------------\n";
	menu.content += "          ";
	menu.content += "MODEL";
	menu.content += " CATALOG        \n";
	menu.content += "-----------------------------\n";
	
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		menu.content += to_string(i+1);
		menu.content += ") ";
		menu.content += shop.get_model(i)->get_name();
		menu.content += " (" + to_string(shop.get_model(i)->get_model_number()) + ")";
		menu.content += "\n";
	}
	menu.content += "\n(0) Go back\n";
	menu.content += "-----------------------------\n\n";
	menu.min = 0;
	menu.max = shop.get_model_size();
	return menu;
}

Menu View::pick_model_menu()
{
	Menu menu;
	menu.content = "---------------";
	menu.content += "Please review your ROBOT MODEL before you continue to order";
	menu.content += "---------------\n";
	menu.content += "(1) View model information\n";
	menu.content += "(2) Continue your order\n";
	menu.content += "(0) Cancel order\n";
	menu.content += "-------------------------------------------\n";
	menu.min = 0;
	menu.max = 2;
	return menu;
}

Menu View::yesno_menu(string prompt)
{
	Menu menu;
	menu.content = prompt;
	menu.content += "\n";
	menu.content += "(1) Yes\n";	
	menu.content += "(0) No\n";
	menu.content += "-----------------------------\n\n";
	menu.min = 0;
	menu.max = 1;
	return menu;
}

void View::ask(string prompt)
{
	cout << prompt << endl;
}

/////////////////////
///////	     ROBOT PARTS
/////////////////////

void View::display_all_parts()
{	
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		display_part(i);
		cout << endl;	
	}
}

string View::all_parts()
{
	string output = "";
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		output += display_string_part(i) + "\n";
	}
	return output;
}

Menu View::display_all_parts(part_t p)
{
	Menu menu;
	menu.content = "-----------------------------\n";
	menu.content += "          ";
	menu.content += part_string(p);
	menu.content += " ROBOT PARTS          \n";
	menu.content += "-----------------------------\n";
	
	int index = 1;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		if (shop.get_part(i)->get_part() == p)
		{
			menu.content += to_string(index);
			menu.content += ") ";
			menu.content += display_string_part(i);
			menu.content += "\n";
			index++;
		}	
	}
	menu.content += "-----------------------------\n\n";
	menu.min = 0;
	menu.max = index-1;
	return menu;
}

void View::display_part(int i)
{
	part_t p = shop.get_part(i)->get_part();
	cout << part_string(p) << endl;
	cout << "Name: "<< shop.get_part(i)->get_name() << endl;
	cout << "Model number: " << shop.get_part(i)->get_model_number() << endl;
	cout << "Cost: $" << shop.get_part(i)->get_cost() << endl;
	cout << "Weight: " << shop.get_part(i)->get_weight() << " lbs"<< endl;
	cout << "Description: " << shop.get_part(i)->get_description() << endl;
	if (p == HEAD)
	{
		cout << "Power: " << shop.get_part(i)->get_power() << " W" << endl;
	}

	if (p == ARM)
	{
		cout << "Max power: " << shop.get_part(i)->get_power() << " W" << endl;
	}	
	
	if (p == LOCOMOTOR)
	{ 
		cout << "Max speed: " << shop.get_part(i)->get_max_speed() << " mph" << endl;
		cout << "Power: " << shop.get_part(i)->get_power() << " W" << endl;
	}
	if (p == BATTERY)
	{
		cout << "Max energy: " << shop.get_part(i)->get_max_energy() << " kWh" << endl;
		cout << "Power available: " << shop.get_part(i)->get_power() << " W" << endl;
	}
	if (p == TORSO)
	{
		cout << "Battery compartments: " << shop.get_part(i)->get_battery_compartments() << endl;
		//cout << "Max arms: " << shop.get_part(i)->get_max_arms() << endl;
	}
}

string View::display_string_part_title(int i)
{
	part_t p = shop.get_part(i)->get_part();
	string result = "(" + part_string(p) + ") ";
	result += shop.get_part(i)->get_name() + " ";
	result += to_string(shop.get_part(i)->get_model_number());
	return result;
}

string View::display_string_part(int i)
{
	part_t p = shop.get_part(i)->get_part();
	string result = part_string(p) + "\n";
	result += "Name: " + shop.get_part(i)->get_name() + "\n";
	result +="Model number: " + to_string(shop.get_part(i)->get_model_number()) + "\n";
	result +="Cost: $" + to_string(shop.get_part(i)->get_cost()) + "\n";
	result +="Weight: " + to_string(shop.get_part(i)->get_weight()) + " lbs"+ "\n";
	result +="Description: " + shop.get_part(i)->get_description() + "\n";
	if (p == HEAD)
	{
		result +="Power: " + to_string(shop.get_part(i)->get_power()) + " W" + "\n";
	}

	if (p == ARM)
	{
		result +="Max power: " + to_string(shop.get_part(i)->get_power()) + " W" +"\n";
	}	
	
	if (p == LOCOMOTOR)
	{ 
		result +="Max speed: " +  to_string(shop.get_part(i)->get_max_speed()) + " mph" +"\n";
		result +="Power: " +  to_string(shop.get_part(i)->get_power()) + " W" + "\n";
	}
	if (p == BATTERY)
	{
		result +="Max energy: " +  to_string(shop.get_part(i)->get_max_energy()) + " kWh" +"\n";
		result +="Power available: " +  to_string(shop.get_part(i)->get_power()) + " W" +"\n";
	}
	if (p == TORSO)
	{
		result +="Battery compartments: " +  to_string(shop.get_part(i)->get_battery_compartments()) + "\n";
		//result +="Max arms: " +  to_string(shop.get_part(i)->get_max_arms()) + "\n";
	}
	return result;
}

vector<string> View::vector_all_part_title()
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		result.push_back(display_string_part_title(i));
	}
	return result;
}

vector<string> View::vector_all_part_details()
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		result.push_back(display_string_part(i));
	}
	return result;
}

vector<string> View::vector_all_part_image()
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		result.push_back(shop.get_part(i)->get_image_filename());
	}
	return result;
}

vector<string> View::vector_all_part_title(part_t p)
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		if (shop.get_part(i)->get_part() != p)
			continue;
		result.push_back(display_string_part_title(i));
	}
	return result;
}

vector<string> View::vector_all_part_details(part_t p)
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		if (shop.get_part(i)->get_part() != p)
			continue;
		result.push_back(display_string_part(i));
	}
	return result;
}

vector<string> View::vector_all_part_image(part_t p)
{
	vector<string> result;
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		if (shop.get_part(i)->get_part() != p)
			continue;
		result.push_back(shop.get_part(i)->get_image_filename());
	}
	return result;
}

string View::part_string(part_t p)
{
	if (p == ARM)
		return "ARM";
	if (p == HEAD)
		return "HEAD";
	if (p == LOCOMOTOR)
		return "LOCOMOTOR";
	if (p == BATTERY)
		return "BATTERY";
	if (p == TORSO)
		return "TORSO";
}

/////////////////////
/////---------------------------End ROBOT PARTS-----------------------
/////////////////////


/////////////////////
//////		ROBOT MODELS
/////////////////////
void View::display_all_models()
{
	cout << "All models: \n" << endl;
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		display_model(i);
	}
	cout << "---------------------------------------------------------\n\n";
}

string View::all_models()
{
	string output = "";
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		output += "(" + to_string(i) + ") \n" + model(i) + "\n";
	}
	return output;
}

void View::display_model(int i)
{
	cout << "Name: " << shop.get_model(i)->get_name() << endl;
	cout << "Model number: " << shop.get_model(i)->get_model_number() << endl;
	cout << "Price: " << shop.get_model(i)->get_price() << endl;
	cout << "Weight: " << shop.get_model(i)->weight() << endl;
	cout << "Max speed: " << shop.get_model(i)->max_speed() << endl;
	cout << "Battery life: " << shop.get_model(i)->max_battery_life() << endl;
	cout << "HEAD: " << shop.get_model(i)->get_head()->get_name() << " " << shop.get_model(i)->get_head()->get_model_number() << endl;
	cout << "LOCOMOTOR: " << shop.get_model(i)->get_locomotor()->get_name() << " " << shop.get_model(i)->get_locomotor()->get_model_number() << endl;
	cout << "TORSO: " << shop.get_model(i)->get_torso()->get_name() << " " << shop.get_model(i)->get_torso()->get_model_number() << endl;
	for (int j = 0; j < 2/*shop.get_model(i).get_torso()->get_max_arms()*/; j++)
	{
		cout << "ARM " << j+1 << ": " << shop.get_model(i)->get_arm(j)->get_name() << " " << shop.get_model(i)->get_arm(j)->get_model_number() << endl;
	}
	for (int j = 0; j < shop.get_model(i)->get_torso()->get_battery_compartments(); j++)
	{
		cout << "BATTERY " << j+1 << ": " << shop.get_model(i)->get_battery(j)->get_name() << " " << shop.get_model(i)->get_battery(j)->get_model_number() << "\n";
	}
}

string View::model_title(int i)
{
	string output = "";
	output += shop.get_model(i)->get_name() + " ";
	output += to_string(shop.get_model(i)->get_model_number());
	return output;
}

string View::model(int i)
{
	string output = "";
	output += "Name: " + shop.get_model(i)->get_name() + "\n";
	output += "Model number: " + to_string(shop.get_model(i)->get_model_number()) + "\n";
	output += "Price: $" + to_string(shop.get_model(i)->get_price()) + "\n";
	output += "Weight: " + to_string(shop.get_model(i)->weight()) + " lbs \n";
	output += "Max speed: " + to_string(shop.get_model(i)->max_speed()) + " mph\n";
	output += "Battery life: " + to_string(shop.get_model(i)->max_battery_life()) + " hrs\n";
	output += "HEAD: " + shop.get_model(i)->get_head()->get_name() + " " + to_string(shop.get_model(i)->get_head()->get_model_number()) + "\n";
	output += "LOCOMOTOR: " + shop.get_model(i)->get_locomotor()->get_name() + " " + to_string(shop.get_model(i)->get_locomotor()->get_model_number()) + "\n";
	output += "TORSO: " + shop.get_model(i)->get_torso()->get_name() + " " + to_string(shop.get_model(i)->get_torso()->get_model_number()) + "\n";
	for (int j = 0; j < 2/*shop.get_model(i).get_torso()->get_max_arms()*/; j++)
	{
		output += "ARM " + to_string(j+1) + ": " + shop.get_model(i)->get_arm(j)->get_name() + " " + to_string(shop.get_model(i)->get_arm(j)->get_model_number()) + "\n";
	}
	for (int j = 0; j < shop.get_model(i)->get_torso()->get_battery_compartments(); j++)
	{
		output += "BATTERY " + to_string(j+1) + ": " + shop.get_model(i)->get_battery(j)->get_name() + " " + to_string(shop.get_model(i)->get_battery(j)->get_model_number()) + "\n";
	}
	return output;
}

vector<string> View::vector_all_model_title()
{
	vector<string> result;
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		result.push_back(model_title(i));
	}
	return result;
}

vector<string> View::vector_all_model_details()
{
	vector<string> result;
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		result.push_back(model(i));
	}
	return result;
}

vector<string> View::vector_all_model_image()
{
	vector<string> result;
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		result.push_back(shop.get_model(i)->get_image_filename());
	}
	return result;
}

string View::display_error_message(part_t p)
{
	string msg = "No " + part_string(p) +" available to create robot model.";
	return msg;
}

///////////
///---------------------End ROBOT MODELS-------------------------
///////////

////////////
/////	CUSTOMER
////////////
string View::display_customer(int i)
{
	string result;
	Customer* c = shop.get_customer(i);
	result = "";
	result += "Name: ";
	result += c->get_name() + "\n";
	result += "Customer number: ";
	result += to_string(c->get_customer_number()) + "\n";
	result += "Phone number: ";
	result += c->get_phone_number() + "\n";
	result += "Email address: ";
	result += c->get_email_address() + "\n";
	return result;
}

string View::display_customer_title(int i)
{
	string result;
	Customer* c = shop.get_customer(i);
	result = "";
	result += c->get_name();
	return result;
}

vector<string> View::vector_all_customer_details()
{
	vector<string> result;
	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		result.push_back(display_customer(i));
	}
	return result;
	
}

vector<string> View::vector_all_customer_title()
{
	vector<string> result;
	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		result.push_back(display_customer_title(i));
	}
	return result;
}

Menu View::customers_menu()
{
	Menu menu;
	menu.content = "LIST OF CUSTOMERS\n\n";
	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		menu.content += "(" + to_string(i+1) + ") " + shop.get_customer(i)->get_name() + " (" + to_string(shop.get_customer(i)->get_customer_number()) + ")\n";
	}
	menu.content += "(0) Cancel\n";
	menu.min = 0;
	menu.max = shop.get_customer_size();
	return menu;
}
////////////
////---------------End CUSTOMER---------------------
	
////////////
/////	Sales associate
////////////
string View::display_sales_associate(int i)
{
	string result;
	Sales_associate* c = shop.get_sales_associate(i);
	result = "";
	result += "Name: ";
	result += c->get_name() + "\n";
	result += "Employee number: ";
	result += to_string(c->get_employee_number()) + "\n";
	return result;
}

string View::sales_associates_list()
{
	string result = "LIST OF SALES ASSOCIATES\n\n";
	for (int i = 0; i < shop.get_sales_associate_size(); i++)
	{
		result += "(" + to_string(i+1) + ") " + shop.get_sales_associate(i)->get_name() + " (" + to_string(shop.get_sales_associate(i)->get_employee_number()) + ")\n";
	}
	return result;
}

Menu View::sales_associates_menu()
{
	Menu menu;
	menu.content = sales_associates_list();
	menu.content += "\n(0) Cancel\n";
	menu.min = 0;
	menu.max = shop.get_sales_associate_size();
	return menu;
}

///////////
///-------------------------End SALES ASSOCIATE------------------
///////////

///////////
///	ORDER
///////////

string View::display_order(int i)
{
	Order* order = shop.get_order(i);
	string result = "";
	result += "Order number: " + to_string(order->get_order_number()) + "\n";
	result += "Date: " + order->get_date();
	result += "Customer: " + order->get_customer()->get_name() + " (" + to_string(order->get_customer()->get_customer_number()) + ")\n";
	result += "SA: " + order->get_sales_associate()->get_name() + " (" + to_string(order->get_sales_associate()->get_employee_number()) + ")\n";
	result += "Robot model: " + order->get_robot_model()->get_name() + " " + to_string(order->get_robot_model()->get_model_number()) + "\n";
	result += "Subtotal: $" + to_string(order->get_price().subtotal) + "\n";
	result += "Tax: $" + to_string(order->get_price().tax) + "\n";
	result += "Shipping: $" + to_string(order->get_price().shipping) + "\n";
	result += "Total: $" + to_string(order->get_price().subtotal+order->get_price().tax+order->get_price().shipping) + "\n";
	result += "Payment status: " + order->get_state_string(1) + "\n";
	result += "Package status: " + order->get_state_string(2) + "\n";
	return result;
}

string View::orders_list()
{
	string result = "-------------VIEW ORDERS------------\n";
	for (int i = 0; i < shop.get_order_size(); i++)
	{
		result += "(" + to_string(i+1) + ") " + to_string(shop.get_order(i)->get_order_number()) + "\n";
	}
	result += "\n(0) Cancel\n";
	result += "-----------------------------------------\n";
	return result;
}
	
Menu View::orders_menu()
{
	Menu menu;
	menu.content = orders_list();
	menu.min = 0;
	menu.max = shop.get_order_size();
	return menu;
}
