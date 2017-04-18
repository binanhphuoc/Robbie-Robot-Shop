#ifndef VIEW_H
#define VIEW_H

#include "Shop.h"
#include "Robot_part.h"
#include "Robot_model.h"
#include "Customer.h"
#include "Sales_associate.h"
#include <string>

using namespace std;

struct Menu
{
	string content;
	int min;
	int max;
};

class View
{
	Shop& shop;
public:
	View(Shop& sh);
	Menu main_menu();
	Menu part_menu();
	Menu model_menu();
	Menu pick_model_menu();
	Menu yesno_menu(string prompt);
	void ask(string prompt);
	
	////////////
	///// 	Robot parts
	////////////
	void display_all_parts();
	string all_parts();
	Menu display_all_parts(part_t p);
	void display_part(int i);
	string display_string_part(int i);
	string part_string(part_t p);
	////////////

	////////////
	/////	Robot models
	////////////
	void display_all_models();
	void display_model(int i);
	void display_error_message(part_t p);
	////////////

	////////////
	/////	Customer
	////////////
	string display_customer(int i);
	Menu customers_menu();
	////////////
	
	////////////
	/////	Sales associate
	////////////
	string display_sales_associate(int i);
	string sales_associates_list();
	Menu sales_associates_menu();
	////////////
	
	////////////
	/////	Order
	////////////
	string display_order(int i);
	string orders_list();
	Menu orders_menu();
	////////////
};

#endif
