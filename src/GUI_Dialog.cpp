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

Input_win::Input_win(int w, int h, const char* title, vector<const char*> entry, Shop& sh, Object _o, void* _p1) : Fl_Window(w, h, title), o(_o), p1(_p1), shop(sh)
{
	begin();
	int y = -30;
	for (int i = 0; i < entry.size(); i++)
	{
		y += 50;
		Fl_Input* in = new Fl_Input(100, y, 140, 30, entry.at(i));
		input.push_back(in);
	}
	
	y += 50;
	
	if (o==PART)
		create = new Fl_Button(70, y, 70, 30, "Create");
	else if (o == MODEL)
		create = new Fl_Button(70, y, 70, 30, "Next");
	
	if (o == PART)
		create->callback(cb_create_part, this);
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

void Input_win::cb_create_part(Fl_Widget* w, void* p)
{
	Input_win* win  = (Input_win*) p;
	win->cb_create_i();
	part_t pt = *( (part_t*)((Input_win*)p)->p1);
	vector<double> output;
	vector<string> org_output = ((Input_win*) p)->get_output();
	if (!Utility::valid_input_part(org_output, pt, output))
	{
		fl_message("Invalid input. Please try again!");
	}
	else
	{
		win->shop.create_new_robot_part(pt, org_output.at(0), (int) output.at(0), output.at(1), output.at(2), org_output.at(4), org_output.at(5), output.at(3), output.at(4));
		string msg = "Robot part has been created successfull\n\n"/* + view.display_string_part(shop.get_part_size()-1)*/;
		fl_message(msg.c_str());
		cb_cancel(w, p);
	}
}

void Input_win::cb_create_part(Fl_Widget* w, void* p)
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
