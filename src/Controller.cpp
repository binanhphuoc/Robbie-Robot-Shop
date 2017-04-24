#include "Robot_part.h"
#include "Robot_model.h"
#include "Shop.h"
#include "View.h"
#include "Controller.h"
#include "GUI_Windows.h"
#include "GUI_MainWin.h"
#include "Utility.h"
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

/*
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
	
}*/
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
void Controller::save()
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
	else 
	{
		cerr << "Unable to open file for saving.\n";
		fl_message("Unable to open file for saving.");
	}	
}

void Controller::load() 
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
	else
	{
		cerr << "Unable to open file for loading.\n";
		fl_message("Unable to open file for loading.");
	}
}

//////----------------------End SAVE AND LOAD----------------------

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

void Controller::main0()
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
	
}

void Controller::main1()
{
	int choice;
	
	choice = Utility::get_cmd(view.part_menu(), "Please select a robot part: ");
	
	if (choice == 0)
	{
		return;
	}
	
	part_t p = (part_t) (choice - 1);
	
	
	string name; //= get_string_input("Name: ");
	int model_number;// = get_int_input("Model number: ");
	double cost;// = get_double_input("Cost: ");
	double weight;// = get_double_input("Weight: ");
	string description;// = get_string_input("Description: ");
	string image_filename;// = get_string_input("Image filename: ");
	
	
	// Create entries for Input_win
	vector<const char*> entry;
	entry.push_back("Name: ");
	entry.push_back("Model \nnumber: ");
	entry.push_back("Cost: ");
	entry.push_back("Weight: ");
	entry.push_back("Description: ");
	entry.push_back("Image \nfilename: ");

	double var1 = 0, var2 = 0;
	int Y = 0;	

	if (p == HEAD)
	{
		//var1 = get_double_input("Power: ");
		entry.push_back("Power: ");
		Y = 420;
	}

	else if (p == ARM)
	{
		//var1 = get_double_input("Max power: ");
		entry.push_back("Max \npower: ");
		Y = 420;
	}	
	
	else if (p == LOCOMOTOR)
	{ 
		//var1 = get_double_input("Max speed: ");
		//var2 = get_double_input("Max power: ");
		entry.push_back("Max \nspeed: ");
		entry.push_back("Max \npower: ");
		Y = 480;
	}
	else if (p == BATTERY)
	{
		//var1 = get_double_input("Max energy: ");
		//var2 = get_double_input("Power available: ");
		entry.push_back("Max \nenergy: ");
		entry.push_back("Power \navailable: ");
		Y = 480;
	}
	else if (p == TORSO)
	{
		//var1 = (double) get_int_input("Battery compartments (1 to 3): ", 1, 3);
		/*var2 = get_double_input("Max arms: ");*/
		entry.push_back("Battery \ncompartments \n(1 to 3): ");
		Y = 420;
	}
	
	
	Input_win* input_win = new Input_win(400, Y, "Create Robot Part", entry, shop, PART, &p);
	
	
	//if (valid)		
	//	input_win->hide();
	//view.display_part(shop.get_part_size()-1);
	//cout << "----------------------------------------------------" << endl;
	//Fl::run();
}

bool Controller::check_available()
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

void Controller::main4()
{
	//cout << "------------------------CREATE NEW ROBOT MODEL----------------------------" << endl;
	if (!check_available())
	{
		fl_message("Unable to create new model.");
		return;
	}

	string name = Utility::get_string_input("Name: ");
	int model_number = Utility::get_int_input("Model number: ");
	vector<Robot_part*> rp;
	
	int choice;
	int cost = 0;
	Robot_part* current = NULL;
	bool power_limited = true;
	double power_consumption = 0, power_available = 0;
	
	while(power_limited)
	{
		power_limited = false;

		choice = Utility::get_cmd(view.display_all_parts(HEAD), "Please select HEAD from the following menu:");
		if (choice == -1)
			return;
		current = shop.get_part(HEAD, choice);
		cost += current->get_cost();
		rp.push_back(current);
		power_consumption += current->get_power();
		//cout << endl;

		
		choice = Utility::get_cmd(view.display_all_parts(TORSO), "Please select TORSO from the following menu:");
		if (choice == -1)
			return;
		Robot_part* torso = shop.get_part(TORSO, choice);
		cost += torso->get_cost();
		rp.push_back(torso);
		//cout << endl;

		choice = Utility::get_cmd(view.display_all_parts(LOCOMOTOR), "Please select LOCOMOTOR from the following menu:");
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
			choice = Utility::get_cmd(view.display_all_parts(ARM), prompt);
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
			choice = Utility::get_cmd(view.display_all_parts(BATTERY), prompt);
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
	double price = Utility::get_double_input(msg);
	shop.create_new_robot_model(name, model_number, price, rp);

	fl_message("Robot model has been created successfully.\n");
	//cout << "----------------------------------------------------" << endl;	
	
}

void Controller::main2()
{
	Fl_Window* win_temp = new Fl_Window{200, 200, "Robot Parts List"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	Fl_Box* whitebox = new Fl_Box(0,0,200,200);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(10, 10, 190, 340);
    	disp->buffer(buff);
	buff->text(view.all_parts().c_str());
	win_temp->end();
	win_temp->show();
	//fl_message_title("ALL ROBOT PARTS");
	//fl_message(view.all_parts().c_str());
}

void Controller::main3()
{
	int choice;
	choice = Utility::get_cmd(view.yesno_menu("Are you sure you want to remove robot part? Any robot model associated with this part will also be removed."));
	if (choice == 0)
		return;
	choice = Utility::get_int_input("Part number: ");
	if (shop.remove_robot_part(choice) == 1)
		cerr << "Part number " << choice << " is out of bound." << endl;
}

void Controller::main5()
{
	Fl_Window* win_temp = new Fl_Window{200, 200, "Robot Models Catalog"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	Fl_Box* whitebox = new Fl_Box(0,0,200,200);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(10, 10, 190, 340);
    	disp->buffer(buff);
	buff->text(view.all_models().c_str());
	win_temp->end();
	win_temp->show();
}

void Controller::main6()
{
	int choice = Utility::get_int_input("Model number: ");
	if (shop.remove_robot_model(choice) == 1)
		cerr << "Model number " << choice << " is out of bound." << endl;
}

void Controller::main7()
{
	cout << "----------------------------------------" << endl;
	cout << "	    CREATE NEW CUSTOMER		 " << endl;
	cout << "----------------------------------------" << endl;
	string name = Utility::get_string_input("Name: ");
	int customer_number = Utility::get_int_input("Customer number: ");
	string phone_number = Utility::get_string_input("Phone number: ");
	string email_address = Utility::get_string_input("Email address: ");
	
	shop.create_new_customer(name, customer_number, phone_number, email_address);

}

void Controller::main8()
{
	cout << "----------------------------------------" << endl;
	cout << "	 VIEW CUSTOMER INFORMATION	 " << endl;
	cout << "----------------------------------------" << endl;
	
	int choice = Utility::get_cmd(view.customers_menu());
	while(choice != 0)
	{
		cout << view.display_customer(choice-1) << endl;
		cout << "----------------------------------------" << endl;
		choice = Utility::get_cmd(view.customers_menu());
	}
	cout << "----------------------------------------" << endl;
}

void Controller::main9()
{
	cout << "----------------------------------------" << endl;
	cout << "	CREATE NEW SALES ASSOCIATE	 " << endl;
	cout << "----------------------------------------" << endl;
	string name = Utility::get_string_input("Name: ");
	int employee_number = Utility::get_int_input("Employee number: ");
	
	shop.create_new_sales_associate(name, employee_number);
}

void Controller::main10()
{
	cout << "----------------------------------------" << endl;
	cout << "	   SALES ASSOCIATE LIST		 " << endl;
	cout << "----------------------------------------" << endl;
	
	cout << view.sales_associates_list() << endl;
	cout << "----------------------------------------" << endl;
}


void Controller::main11()
{
	cout << "----------------------------------------" << endl;
	cout << "	    CREATE NEW ORDER		 " << endl;
	cout << "----------------------------------------" << endl;
	
	int order_number = Utility::get_int_input("Order number: ");
	
	int choice1; 
	
	int choice2 = 0;
	while(choice2 == 0)
	{	
		choice1 = Utility::get_cmd(view.pick_model_menu());
		while (choice1 == 1)
		{
			choice2 = Utility::get_cmd(view.model_menu());
			while (choice2 != 0)
			{
				view.display_model(choice2-1);
				choice2 = Utility::get_cmd(view.model_menu());
			}
			choice1 = Utility::get_cmd(view.pick_model_menu());
		}
	
		if (choice1 == 0)
			return;
		
		choice2 = Utility::get_cmd(view.model_menu());
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
	choice = Utility::get_cmd(view.sales_associates_menu());
	if (choice == 0)
		return;
	Sales_associate* sa = shop.get_sales_associate(choice-1);
	
	choice = Utility::get_cmd(view.customers_menu());
	if (choice == 0)
		return;
	Customer* c = shop.get_customer(choice-1);

	shop.create_new_order(order_number, rm, price, sa, c);
	cout << "----------------------------------------" << endl;
}

void Controller::main12()
{
	int choice = Utility::get_cmd(view.orders_menu());
	string temp;
	while(choice != 0)
	{
		cout << view.display_order(choice-1) << endl;
		cout << "Press Enter to continue" << endl;
		getline(cin, temp);
		choice = Utility::get_cmd(view.orders_menu());
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
	Shop sh;
	View v(sh);
	Controller c(sh, v);
	run_main_win(400, 300, "Robbie Robot Shop", c);
	return 0;
}
