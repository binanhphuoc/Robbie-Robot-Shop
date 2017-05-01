#include "Robot_part.h"
#include "Robot_model.h"
#include "Shop.h"
#include "View.h"
#include "Controller.h"
#include "GUI_Dialog.h"
#include "GUI_MainWin.h"
#include "Utility.h"
#include "Dialog_manager.h"
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


void Controller::run(){

	int cmd;
	load();
	
	GUI_MainWin* main_win = new GUI_MainWin(400, 300, "Robbie Robot Shop", *this);
/*
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
*/
	//Fl::run();
	
}

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
	Create_part_dialog cp(shop, view);
}


bool Controller::check_available()
{
	bool available = true;
	string error_msg = "";
	if (shop.get_part_size(HEAD) == 0)
	{
		error_msg += view.display_error_message(HEAD) + "\n";
		available = false;
	}
	if (shop.get_part_size(TORSO) == 0)
	{
		error_msg += view.display_error_message(TORSO) + "\n";
		available = false;
	}
	if (shop.get_part_size(LOCOMOTOR) == 0)
	{
		error_msg += view.display_error_message(LOCOMOTOR)+ "\n";
		available = false;
	}
	if (shop.get_part_size(ARM) == 0)
	{
		error_msg += view.display_error_message(ARM)+ "\n";
		available = false;
	}
	if (shop.get_part_size(BATTERY) == 0)
	{
		error_msg += view.display_error_message(BATTERY)+ "\n";
		available = false;
	}
	if (!available)
	{
		error_msg += "Unable to create new model.";
		fl_message(error_msg.c_str());
	}
	return available;
}

void Controller::main4()
{
	//cout << "------------------------CREATE NEW ROBOT MODEL----------------------------" << endl;
	if (!check_available())
	{
		return;
	}

/*
	vector<const char*> entry;
	entry.push_back("Name: ");
	entry.push_back("Model \nnumber: ");
	//string name = Utility::get_string_input("Name: ");
	//int model_number = Utility::get_int_input("Model number: ");
	
	Input_win* input_win = new Input_win(300, 170, "Create Robot Model", entry, shop, view, MODEL);
	//cout << "----------------------------------------------------" << endl;	
*/
	Create_model_dialog md(shop, view);

}

void Controller::main2()
{
	Display_part_dialog dp(view);
/*
	Fl_Window* win_temp = new Fl_Window{300, 350, "Robot Parts List"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	//Fl_Box* whitebox = new Fl_Box(0,0,200,200);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(5, 5, 290, 340);
    	disp->buffer(buff);
	buff->text(view.all_parts().c_str());
	win_temp->resizable(*disp);
	win_temp->end();
	win_temp->show();
*/
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
	Fl_Window* win_temp = new Fl_Window{300, 350, "Robot Models Catalog"};
	win_temp->callback([](Fl_Widget* w, void* p){w->hide();});
	Fl_Box* whitebox = new Fl_Box(0,0,200,200);
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    	Fl_Text_Display *disp = new Fl_Text_Display(5, 5, 290, 340);
    	disp->buffer(buff);
	buff->text(view.all_models().c_str());
	win_temp->resizable(*disp);
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
