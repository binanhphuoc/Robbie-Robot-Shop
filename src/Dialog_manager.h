#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "Robot_part.h"
#include "Browser_dialog.h"
#include "Utility.h"
#include "Input_dialog.h"
#include "Create_account_dialog.h"
#include "Browser_dialog.h"
#include "Login_dialog.h"
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
/////		NEW ACCOUNT
////////////////////

class New_account
{
public:
	New_account(Shop& sh);
	Create_account_dialog* cd;
	Input_dialog* infoDialog;

	Role role;
	string username;
	string password;
	Shop& shop;

	vector<Fl_Callback*> vCB;

	static void acceptAccountCB(Fl_Widget* w, void* p);
	static void createAccountCB(Fl_Widget* w, void* p);
};

/////--------------------------------------------------------------

////////////////////
/////		LOGIN DIALOG
////////////////////

class Login_window
{
public:
	Login_window(Shop& sh, Role& r, int& position, bool& exit);
	Login_dialog* ld;
	New_account* na;

	bool& exit;
	int& position;
	Shop& shop;
	Role& role;
	
private:
	static void loginCB(Fl_Widget* w, void* p); 
	static void createloginCB(Fl_Widget* w, void* p);
	static void exitCB(Fl_Widget* w, void* p);
};

/////--------------------------------------------------------------

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

/////////////////
//////		DISPLAY MODEL DIALOG
/////////////////

class Display_model_dialog
{
public:
	Display_model_dialog(View& v);
	Browser_dialog* browser;
	View& view;
	
	vector<Fl_Callback*> vCB;

	static void browserCB(Fl_Widget* w, void* p);
};

/////---------------------------------------------------------

/////////////////
//////		CHOOSE MODEL DIALOG
/////////////////

class Choose_model_dialog
{
public:
	Choose_model_dialog(View& v);
	Browser_dialog* browser;
	View& view;

	int choice;	

	vector<Fl_Callback*> vCB;

	static void browserCB(Fl_Widget* w, void* p);
};

/////---------------------------------------------------------

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
	string image_filename;
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

/////////////////
//////		CREATE SALES ASSOCIATE DIALOG
/////////////////

class Create_sa_dialog
{
public:
	Create_sa_dialog(Shop& sh, Role r);
	Input_dialog* infoDialog;
	Create_account_dialog* passDialog;
	
	Shop& shop;
	Role role;
	vector<Fl_Callback*> vCB;

	string name;
	int employee_number;
	string username;
	string password;

	///// Callbacks

	static void infoCB(Fl_Widget* w, void* p);
	static void passCB(Fl_Widget* w, void* p);
	
};

/////---------------------------------------------------------

/////////////////
//////		CREATE BELOVED CUSTOMER DIALOG
/////////////////

class Create_bc_dialog
{
public:
	Create_bc_dialog(Shop& sh, Role r);
	Input_dialog* infoDialog;
	Create_account_dialog* passDialog;
	
	Shop& shop;
	Role role;
	vector<Fl_Callback*> vCB;

	string name;
	int number;
	string phone;
	string email;
	string username;
	string password;

	///// Callbacks

	static void infoCB(Fl_Widget* w, void* p);
	static void passCB(Fl_Widget* w, void* p);
	
};

/////---------------------------------------------------------

/////////////////
//////		CREATE NEW ORDER
/////////////////

class Create_order_dialog
{
public:
	Create_order_dialog(Shop& sh, View& v, int sa);
	Browser_dialog* bd;
	Input_dialog* id;
	Browser_dialog* md;
	
	Shop& shop;
	View& view;
	vector<Fl_Callback*> vCB;

	int order_number;
	int robot_model;
	Price price;
	int sa;
	int bc;

	///// Callbacks

	static void bdCB(Fl_Widget* w, void* p);
	static void idCB(Fl_Widget* w, void* p);
	static void mdCB(Fl_Widget* w, void* p);
	
};

/////---------------------------------------------------------

#endif
