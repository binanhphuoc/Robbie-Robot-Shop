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

class Controller
{
public:
	Controller(Shop& sh, View& v) : shop(sh), view(v) {}
	void run();

	////// Save and Load
	void save();
	void load();

	////// Main Menu
	//void MainMenuCmd(int cmd);
	void main0();
	void main1();
	bool check_available();
	void main2();
	void main3();
	void main4();
	void main5();
	void main6();
	void main7();
	void main8();
	void main9();
	void main10();
	void main11();
	void main12();
	//////

private:
	Shop& shop;
	View& view;
};

#endif
