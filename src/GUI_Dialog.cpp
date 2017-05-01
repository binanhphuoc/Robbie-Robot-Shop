#include "GUI_Dialog.h"
#include "Robot_part.h"
#include "Utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Input_win::Input_win(int w, int h, const char* title, vector<const char*> entry, Shop& sh, View& v, Object _o, void* _p1) : Fl_Window(w, h, title), o(_o), p1(_p1), shop(sh), view(v)
{
	begin();
	int y = -30;
	for (int i = 0; i < entry.size(); i++)
	{
		y += 50;
		Fl_Input* in = new Fl_Input(120, y, 140, 30, entry.at(i));
		input.push_back(in);
	}
	
	y += 50;
	
	if (o==PART)
		create = new Fl_Button(70, y, 70, 30, "Create");
	else if (o == MODEL)
		create = new Fl_Button(70, y, 70, 30, "Next");
	
	if (o == MODEL)
		create->callback(cb_create_model, this);

	cancel = new Fl_Button(160, y, 70, 30, "Cancel");
	cancel->callback(cb_cancel, this);

	end();
	resizable(this);
	show();
	Fl::run();
}

void Input_win::cb_cancel(Fl_Widget* w, void* p)
{
	((Input_win*) p)->cb_cancel_i();
}

void Input_win::cb_cancel_i()
{
	hide();
}

void Input_win::cb_create_model(Fl_Widget* w, void* p)
{
	Input_win* win  = (Input_win*) p;
	win->cb_create_i();
	string name;
	int model_number;
	if (!Utility::valid_int_input(win->get_output().at(1), model_number))
		fl_message("Invalid input. Please try again!");
	else
	{
		win->hide();
				
		Shop& shop = win->shop;
		View& view = win->view;

		vector<Robot_part*> rp;
	
		int choice;
		int cost = 0;
		Robot_part* current = NULL;
		bool power_limited = true;
		double power_consumption = 0, power_available = 0;
	
		while(power_limited)
		{
			power_limited = false;

			choice = Utility::get_cmd(view.display_all_parts(HEAD), "Please select HEAD from the following menu:", "Create Robot Model");
			if (choice == 0)
				return;
			current = shop.get_part(HEAD, choice-1);
			cost += current->get_cost();
			rp.push_back(current);
			power_consumption += current->get_power();
			//cout << endl;

		
			choice = Utility::get_cmd(view.display_all_parts(TORSO), "Please select TORSO from the following menu:", "Create Robot Model");
			if (choice == 0)
				return;
			Robot_part* torso = shop.get_part(TORSO, choice-1);
			cost += torso->get_cost();
			rp.push_back(torso);
			//cout << endl;

			choice = Utility::get_cmd(view.display_all_parts(LOCOMOTOR), "Please select LOCOMOTOR from the following menu:", "Create Robot Model");
			if (choice == 0)
				return;
			current = shop.get_part(LOCOMOTOR, choice-1);
			cost += current->get_cost();
			rp.push_back(current);
			power_consumption += current->get_power();
			//cout << endl;
	
			for (int i = 0; i < 2/*torso->get_max_arms()*/; i++)
			{
				string prompt = "Please select ARM " + to_string(i+1) + " from the following menu:";
				if (choice == 0)
					return;
				choice = Utility::get_cmd(view.display_all_parts(ARM), prompt, "Create Robot Model");
				current = shop.get_part(ARM, choice-1);
				cost += current->get_cost();
				rp.push_back(current);
				power_consumption += current->get_power();
				//cout << endl;
			}
	
			for (int i = 0; i < torso->get_battery_compartments(); i++)
			{
				string prompt =  "Please select BATTERY " + to_string(i+1) + " from the following menu:";
				if (choice == 0)
					return;
				choice = Utility::get_cmd(view.display_all_parts(BATTERY), prompt, "Create Robot Model");
				current = shop.get_part(BATTERY, choice-1);
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
	}
}

void Input_win::cb_create_i()
{
	clear_output();
	for (int i = 0; i< input.size(); i++)
	{
		add_output(input.at(i)->value());
	}
	changed = true;
}

void Input_win::add_output(const char* in)
{
	//string str = in;
	//cout << str << endl;	
	output.push_back(in);
}

vector<string> Input_win::get_output()
{
	return output;
}

void Input_win::clear_output()
{
	output.clear();
}

/*
vector<string> run_input_win(int w, int h, const char* title, vector<const char*> entry)
{
	Input_win* iw = new Input_win(w, h, title, entry);
	return iw->get_output();
}*/

/*
void* get_ptr()
{
	return ptr;
}*/
