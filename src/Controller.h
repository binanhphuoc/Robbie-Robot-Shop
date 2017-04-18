#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "View.h"
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

void run();
	
////// Save and Load
void save();
void load();

int get_cmd(Menu menu, string prompt = "");
bool valid_cmd(string choice, int min, int max, int& ch);
bool valid_int_input(string input, int& ch);
bool valid_double_input(string input, double& ch);
string get_string_input(string prompt);
int get_int_input(string prompt, int min = -1, int max = -1);
double get_double_input(string prompt);

////// Main Menu
void MainMenuCmd(int cmd);
void main0(Fl_Widget* w, void* p);
void main1(Fl_Widget* w, void* p);
bool check_available();
void main2(Fl_Widget* w, void* p);
void main3();
void main4(Fl_Widget* w, void* p);
void main5(Fl_Widget* w, void* p);
void main6();
void main7();
void main8();
void main9();
void main10();
void main11();
void main12();
//////

int X = 400;
int bsize = 50;
int Y = 80+bsize;

Shop shop;
View view(shop);
Fl_Window* win;
Fl_Menu_Item menuitems[] = { 
	{"&File", 0, 0, 0, FL_SUBMENU},
		{ "&Exit", FL_ALT + FL_F + 4, main0},
		{0},
	{"&Create", 0, 0, 0, FL_SUBMENU},
		{ "Robot &Component", 0, main1},
		{ "Robot &Model", 0, main4},
		{0},
	{"&View", 0, 0, 0, FL_SUBMENU},
		{ "Robot &Part", FL_ALT + 'p', main2},
		{ "Robot &Model", FL_ALT + 'm', main5},
		{0},
	{0}
};

#endif
