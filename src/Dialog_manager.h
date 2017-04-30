#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "Robot_part.h"
#include "Browser_dialog.h"
#include "Utility.h"
#include "Input_dialog.h"
#include "View.h"
#include "Shop.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>

using namespace std;

class Display_part_dialog
{
public:
	Display_part_dialog(View& v);
	Browser_dialog* browser;
	View& view;
	
	vector<Fl_Callback*> vCB;

	static void browserCB(Fl_Widget* w, void* p);
};

class Create_part_dialog
{
public:
	Create_part_dialog(Shop& sh, View& v);
	Input_dialog* dialog;
	View& view;
	Shop& shop;
	part_t pt;
	
	vector<Fl_Callback*> vCB;

	static void dialogCB(Fl_Widget* w, void* p);
};

#endif
