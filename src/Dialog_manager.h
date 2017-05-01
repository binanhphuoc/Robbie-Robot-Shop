#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "Robot_part.h"
#include "Browser_dialog.h"
#include "Utility.h"
#include "Input_dialog.h"
#include "Browser_dialog.h"
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

////////////////////
////		DISPLAY PART DIALOG
////////////////////

class Display_part_dialog
{
public:
	Display_part_dialog(View& v);
	Browser_dialog* browser;
	View& view;
	
	vector<Fl_Callback*> vCB;

	static void browserCB(Fl_Widget* w, void* p);
};

//////------------------------------------------------------

/////////////////////
///////		CREATE PART DIALOG
/////////////////////

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

/////-------------------------------------------------------

/////////////////
//////		CREATE MODEL DIALOG
/////////////////

class Create_model_dialog
{
public:
	Create_model_dialog(Shop& sh, View& v);
	Input_dialog* infoDialog; // This dialog get model name and model number
	Browser_dialog* browser;
	View& v;
	Shop& shop;

	///// Variables for creating
	vector<Robot_part*> rp;
	string name;
	int model_number;
	double price;
	int handcount = 2;
	int batterycount = 0;
	double cost = 0;
	double power_available = 0;
	double power_consumption = 0;
	

	//part_t pt; //This is the part of the current dialog displayed
	
	vector<Fl_Callback*> vCB;

	static void infoDialogCB(Fl_Widget* w, void* p);
	static void headDialogCB(Fl_Widget* w, void* p);
	static void torsoDialogCB(Fl_Widget* w, void* p);
	static void locomotorDialogCB(Fl_Widget* w, void* p);
	static void armDialogCB(Fl_Widget* w, void* p);
	static void batteryDialogCB(Fl_Widget* w, void* p);
};

/////---------------------------------------------------------

#endif
