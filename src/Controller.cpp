#include "Robot_part.h"
#include "Robot_model.h"
#include "Shop.h"
#include "View.h"
#include "Controller.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

using namespace std;

int gui(){

	int cmd;
	load();

	// Create a window
	win = new Fl_Window{X, Y, "Robbie Robot Shop"};
	win->color(FL_WHITE);
	
	// Sign up for callback
	win->callback(main0);

	// View
	Fl_Box* whitebox = new Fl_Box(0,0,X,Y);
	
	// Install menu bar
	
	Fl_Menu_Bar* menubar = new Fl_Menu_Bar(0, 0, X, 30);
	menubar->menu(menuitems);
	
	win->end();
	win->show();
	return (Fl::run());
	
}
/*
void run()
{
	int cmd;
	load();
	cmd = get_cmd(view.main_menu());
	while(cmd != 0)
	{
		MainMenuCmd(cmd);
		cmd = get_cmd(view.main_menu());
	}
	main0();
}
*/
////// Save and Load
void save()
{
	ofstream ost("data.txt");
	if (ost.is_open())
	{
		shop.save_part(ost);
		shop.save_model(ost);
		shop.save_customer(ost);
		shop.save_sales_associate(ost);
		shop.save_order(ost);
		ost.close();
	}
	else cerr << "Unable to open file for saving.\n";	
}

void load() 
{
	ifstream ist("data.txt");
	if (ist.is_open())
	{
		shop.load_part(ist);
		shop.load_model(ist);
		shop.load_customer(ist);
		shop.load_sales_associate(ist);
		shop.load_order(ist);
		ist.close();
	}
	else cerr << "Unable to open file for loading.\n";
}

//////----------------------End SAVE AND LOAD----------------------

int get_cmd(Menu menu, string prompt)
{
	const char* choice;
	int ch;
	//cout << menu.content;
	string msg = menu.content + "\n" + prompt;
	choice = fl_input(msg.c_str(),"");
	//view.ask("Choice: ");
	//getline(cin, choice);
	if (choice == NULL)
		return -1;
	string choice_str = choice;
	while (!valid_cmd(choice_str, menu.min, menu.max, ch))
	{	
		fl_alert("Invalid input. Please try again!\n\n");
		choice = fl_input(menu.content.c_str(),"");
		if (choice == NULL)
			return -1;
		choice_str = choice;
	}
	
	return ch;
}

bool valid_cmd(string choice, int min, int max, int& ch)
{
	if (!valid_int_input(choice, ch))
	{
		return false;
	}	
	if (ch < min || ch > max)
	{
		return false;
	}
	else
		return true;
}

bool isDigit(char c)
{
	if (c == '0' || c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
		return true;
	return false;
}

bool valid_int_input(string input, int& ch)
{
	const char* str = input.c_str();
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isDigit(str[i]))
		{
			ch = 0;
			return false;
		}
	}
	
	ch = atoi(str);
	//cout << "char = " << ch << endl;
	return true;
}
	
bool valid_double_input(string input, double& ch)
{
	const char* str = input.c_str();
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isDigit(str[i]) && str[i] != '.')
		{
			ch = 0;
			return false;
		}
	}
	
	ch = atof(str);
	//cout << "char = " << ch << endl;
	return true;
}

string get_string_input(string prompt)
{	
	string input = fl_input(prompt.c_str());
	return input;
}

int get_int_input(string prompt, int min, int max)
{
	//view.ask(prompt);
	string input = fl_input(prompt.c_str());
	int in;
	if (min == -1 || max == -1)
	{
		while (!valid_int_input(input, in))
		{
			fl_alert("Invalid input. Please try again!\n\n");
			input = fl_input(prompt.c_str());
		}
		return in;
	}
	else
	{
		while (!valid_cmd(input, min, max, in))
		{
			string msg = "Input should be a number between " + to_string(min) + " and " + to_string(max) + ". Please try again!\n\n";
			fl_message(msg.c_str());
			input = fl_input(prompt.c_str());
		}
		return in;
	}
}

double get_double_input(string prompt)
{
	string input = fl_input(prompt.c_str());
	double in;
	while (!valid_double_input(input, in))
	{
		fl_alert("Invalid input. Please try again!\n\n");
		input = fl_input(prompt.c_str());
	}
	return in;
}

//////////////////////////////
/////////	MAIN MENU
//////////////////////////////

/*
void MainMenuCmd(int cmd)
{
	if (cmd == 1)
	{
		main1();
	}
	else if (cmd == 2)
	{
		main2();
	}
	else if (cmd == 3)
	{
		main3();
	}
	else if (cmd == 4)
	{
		main4();
	}
	else if (cmd == 5)
	{
		main5();
	}
	else if (cmd == 6)
	{
		main6();
	}
	else if (cmd == 7)
	{
		main7();
	}
	else if (cmd == 8)
	{
		main8();
	}
	else if (cmd == 9)
	{
		main9();
	}
	else if (cmd == 10)
	{
		main10();
	}
	else if (cmd == 11)
	{
		main11();
	}
	else if (cmd == 12)
	{
		main12();
	}
}
*/

void main0(Fl_Widget* w, void* p)
{
	save();	

	for (int i = 0; i < shop.get_order_size(); i++)
	{
		shop.remove_order(i);
	}
	for (int i = 0; i < shop.get_model_size(); i++)
	{
		shop.remove_robot_model(i);
	}
	for (int i = 0; i < shop.get_part_size(); i++)
	{
		shop.remove_robot_part(i);
	}
	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		shop.remove_customer(i);
	}
	for (int i = 0; i < shop.get_sales_associate_size(); i++)
	{
		shop.remove_sales_associate(i);
	}
	
	win->hide();
}

void main1(Fl_Widget* w, void* pp)
{
	//cout << "------------------------CREATE NEW ROBOT PART----------------------------" << endl;
	int choice;
	
	
	choice = get_cmd(view.part_menu(), "Please select a robot part: ");
	
	if (choice == 0)
	{
		//cout << "----------------------------------------------------" << endl;
		return;
	}
	
	part_t p = (part_t) (choice - 1);
	
	string name = get_string_input("Name: ");
	int model_number = get_int_input("Model number: ");
	double cost = get_double_input("Cost: ");
	double weight = get_double_input("Weight: ");
	string description = get_string_input("Description: ");
	string image_filename = get_string_input("Image filename: ");

	double var1 = 0, var2 = 0;
	
	if (p == HEAD)
	{
		var1 = get_double_input("Power: ");
	}

	if (p == ARM)
	{
		var1 = get_double_input("Max power: ");
	}	
	
	if (p == LOCOMOTOR)
	{ 
		var1 = get_double_input("Max speed: ");
		var2 = get_double_input("Max power: ");
	}
	if (p == BATTERY)
	{
		var1 = get_double_input("Max energy: ");
		var2 = get_double_input("Power available: ");
	}
	if (p == TORSO)
	{
		var1 = (double) get_int_input("Battery compartments (1 to 3): ", 1, 3);
		/*var2 = get_double_input("Max arms: ");*/
	}

	//cout << name << " " << model_number << " " << cost << " " << weight << " " << description << " " << image_filename << " " << var1 << " " << var2 << endl;
	shop.create_new_robot_part(p, name, model_number, cost, weight, description, image_filename, var1, var2);
	string msg = "Robot part has been created successfully with following details:\n\n" + view.display_string_part(shop.get_part_size()-1);
	fl_message(msg.c_str());
	//view.display_part(shop.get_part_size()-1);
	//cout << "----------------------------------------------------" << endl;
}

bool check_available()
{
	bool available = true;
	if (shop.get_part_size(HEAD) == 0)
	{
		view.display_error_message(HEAD);
		available = false;
	}
	if (shop.get_part_size(TORSO) == 0)
	{
		view.display_error_message(TORSO);
		available = false;
	}
	if (shop.get_part_size(LOCOMOTOR) == 0)
	{
		view.display_error_message(LOCOMOTOR);
		available = false;
	}
	if (shop.get_part_size(ARM) == 0)
	{
		view.display_error_message(ARM);
		available = false;
	}
	if (shop.get_part_size(BATTERY) == 0)
	{
		view.display_error_message(BATTERY);
		available = false;
	}
	return available;
}

void main4(Fl_Widget* w, void* p)
{
	//cout << "------------------------CREATE NEW ROBOT MODEL----------------------------" << endl;
	if (!check_available())
	{
		fl_message("Unable to create new model.");
		return;
	}

	string name = get_string_input("Name: ");
	int model_number = get_int_input("Model number: ");
	vector<Robot_part*> rp;
	
	int choice;
	int cost = 0;
	Robot_part* current = NULL;
	bool power_limited = true;
	double power_consumption = 0, power_available = 0;
	
	while(power_limited)
	{
		power_limited = false;

		choice = get_cmd(view.display_all_parts(HEAD), "Please select HEAD from the following menu:");
		if (choice == -1)
			return;
		current = shop.get_part(HEAD, choice);
		cost += current->get_cost();
		rp.push_back(current);
		power_consumption += current->get_power();
		//cout << endl;

		
		choice = get_cmd(view.display_all_parts(TORSO), "Please select TORSO from the following menu:");
		if (choice == -1)
			return;
		Robot_part* torso = shop.get_part(TORSO, choice);
		cost += torso->get_cost();
		rp.push_back(torso);
		//cout << endl;

		choice = get_cmd(view.display_all_parts(LOCOMOTOR), "Please select LOCOMOTOR from the following menu:");
		if (choice == -1)
			return;
		current = shop.get_part(LOCOMOTOR, choice);
		cost += current->get_cost();
		rp.push_back(current);
		power_consumption += current->get_power();
		//cout << endl;
	
		for (int i = 0; i < 2/*torso->get_max_arms()*/; i++)
		{
			string prompt = "Please select ARM " + to_string(i+1) + " from the following menu:";
			if (choice == -1)
				return;
			choice = get_cmd(view.display_all_parts(ARM), prompt);
			current = shop.get_part(ARM, choice);
			cost += current->get_cost();
			rp.push_back(current);
			power_consumption += current->get_power();
			//cout << endl;
		}
	
		for (int i = 0; i < torso->get_battery_compartments(); i++)
		{
			string prompt =  "Please select BATTERY " + to_string(i+1) + " from the following menu:";
			if (choice == -1)
				return;
			choice = get_cmd(view.display_all_parts(BATTERY), prompt);
			current = shop.get_part(BATTERY, choice);
			cost += current->get_cost();
			rp.push_back(current);
			power_available += current->get_power();
			//cout << endl;
		}
		
		if (power_available < power_consumption)
		{
			power_limited = true;
			cost = 0;
			power_consumption = 0; power_available = 0;
			rp.clear();
			fl_alert("Limited power (from batteries) to support other parts. Please choose again!");
		}
	}
	string msg= "Total cost of this model is $" + to_string(cost) + "\n\nPrice: ";
	double price = get_double_input(msg);
	shop.create_new_robot_model(name, model_number, price, rp);

	fl_message("Robot model has been created successfully.\n");
	//cout << "----------------------------------------------------" << endl;	
	
}

void main2(Fl_Widget* w, void* p)
{
	Fl_Window* win_temp = new Fl_Window{X, Y+150, "Robot Parts List"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	Fl_Box* whitebox = new Fl_Box(0,0,X,Y+150);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(10, 10, X-10, Y+140);
    	disp->buffer(buff);
	buff->text(view.all_parts().c_str());
	win_temp->end();
	win_temp->show();
	//fl_message_title("ALL ROBOT PARTS");
	//fl_message(view.all_parts().c_str());
}

void main3()
{
	int choice;
	choice = get_cmd(view.yesno_menu("Are you sure you want to remove robot part? Any robot model associated with this part will also be removed."));
	if (choice == 0)
		return;
	choice = get_int_input("Part number: ");
	if (shop.remove_robot_part(choice) == 1)
		cerr << "Part number " << choice << " is out of bound." << endl;
}

void main5(Fl_Widget* w, void* p)
{
	Fl_Window* win_temp = new Fl_Window{X, Y+150, "Robot Models Catalog"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	Fl_Box* whitebox = new Fl_Box(0,0,X,Y+150);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(10, 10, X-10, Y+140);
    	disp->buffer(buff);
	buff->text(view.all_models().c_str());
	win_temp->end();
	win_temp->show();
}

void main6()
{
	int choice = get_int_input("Model number: ");
	if (shop.remove_robot_model(choice) == 1)
		cerr << "Model number " << choice << " is out of bound." << endl;
}

void main7()
{
	cout << "----------------------------------------" << endl;
	cout << "	    CREATE NEW CUSTOMER		 " << endl;
	cout << "----------------------------------------" << endl;
	string name = get_string_input("Name: ");
	int customer_number = get_int_input("Customer number: ");
	string phone_number = get_string_input("Phone number: ");
	string email_address = get_string_input("Email address: ");
	
	shop.create_new_customer(name, customer_number, phone_number, email_address);

}

void main8()
{
	cout << "----------------------------------------" << endl;
	cout << "	 VIEW CUSTOMER INFORMATION	 " << endl;
	cout << "----------------------------------------" << endl;
	
	int choice = get_cmd(view.customers_menu());
	while(choice != 0)
	{
		cout << view.display_customer(choice-1) << endl;
		cout << "----------------------------------------" << endl;
		choice = get_cmd(view.customers_menu());
	}
	cout << "----------------------------------------" << endl;
}

void main9()
{
	cout << "----------------------------------------" << endl;
	cout << "	CREATE NEW SALES ASSOCIATE	 " << endl;
	cout << "----------------------------------------" << endl;
	string name = get_string_input("Name: ");
	int employee_number = get_int_input("Employee number: ");
	
	shop.create_new_sales_associate(name, employee_number);
}

void main10()
{
	cout << "----------------------------------------" << endl;
	cout << "	   SALES ASSOCIATE LIST		 " << endl;
	cout << "----------------------------------------" << endl;
	
	cout << view.sales_associates_list() << endl;
	cout << "----------------------------------------" << endl;
}


void main11()
{
	cout << "----------------------------------------" << endl;
	cout << "	    CREATE NEW ORDER		 " << endl;
	cout << "----------------------------------------" << endl;
	
	int order_number = get_int_input("Order number: ");
	
	int choice1; 
	
	int choice2 = 0;
	while(choice2 == 0)
	{	
		choice1 = get_cmd(view.pick_model_menu());
		while (choice1 == 1)
		{
			choice2 = get_cmd(view.model_menu());
			while (choice2 != 0)
			{
				view.display_model(choice2-1);
				choice2 = get_cmd(view.model_menu());
			}
			choice1 = get_cmd(view.pick_model_menu());
		}
	
		if (choice1 == 0)
			return;
		
		choice2 = get_cmd(view.model_menu());
	}

	Robot_model* rm = shop.get_model(choice2-1); 
	
	Price price;
	price.subtotal = rm->get_price();
	cout << "Subtotal: $" << to_string(price.subtotal) << endl;
	price.tax = price.tax*price.subtotal;	
	cout << "Tax: $" << to_string(price.tax) << endl;
	price.shipping = 15 * rm->weight() / 100;
	cout << "Tax: $" << to_string(price.shipping) << endl;

	int choice;
	choice = get_cmd(view.sales_associates_menu());
	if (choice == 0)
		return;
	Sales_associate* sa = shop.get_sales_associate(choice-1);
	
	choice = get_cmd(view.customers_menu());
	if (choice == 0)
		return;
	Customer* c = shop.get_customer(choice-1);

	shop.create_new_order(order_number, rm, price, sa, c);
	cout << "----------------------------------------" << endl;
}

void main12()
{
	int choice = get_cmd(view.orders_menu());
	string temp;
	while(choice != 0)
	{
		cout << view.display_order(choice-1) << endl;
		cout << "Press Enter to continue" << endl;
		getline(cin, temp);
		choice = get_cmd(view.orders_menu());
	}
}

//////////////////////////////
//////////////////////////////
//////////////////////////////


//////////////////////////////
/////		MAIN
//////////////////////////////

int main()
{
	return(gui());
}
