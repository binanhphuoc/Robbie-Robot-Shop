#include "Dialog_manager.h"
#include "Browser_dialog.h"
#include "Input_dialog.h"
#include <FL/Fl.H>
#include <iostream>
#include <sstream>

////////////////////
/////		LOGIN DIALOG
////////////////////

New_account::New_account(Shop& sh) : shop(sh)
{
	vCB.push_back(acceptAccountCB);
	vCB.push_back(createAccountCB);
	cd = new Create_account_dialog("Create new account", vCB, this, true);
	Fl::run();
}

void New_account::acceptAccountCB(Fl_Widget* w, void* p)
{	
	New_account* na = (New_account*) p;
	Create_account_dialog* cd = na->cd;
	
	string username = cd->username->value();
	string password = cd->password->value();
	string confirm = cd->confirm->value();

	if (password != confirm || password == "" || username == "")
	{
		fl_message("Please confirm your password again.");
		return;
	}
	
	if (!Utility::valid_account(na->shop, username))
	{
		fl_message("This username has been taken. Please pick another username.");
		return;
	}
	na->role = (Role) cd->role->value();
	na->username = username;
	na->password = password;

	cd->hide();
	
	vector<const char*> entry;
	if (na->role == BC)
	{
		entry.push_back("Name: ");
		entry.push_back("Customer \nnumber: ");
		entry.push_back("Phone \nnumber: ");
		entry.push_back("Email \naddress: ");
		na->infoDialog = new Input_dialog("Customer \ninformation", entry, na->vCB, na);
	}
	else if (na->role == SA)
	{
		entry.push_back("Name: ");
		entry.push_back("Employee \nnumber: ");
		na->infoDialog = new Input_dialog("Sales associate information", entry, na->vCB, na);
	}
}

void New_account::createAccountCB(Fl_Widget* w, void* p)
{
	New_account* na = (New_account*) p;
	Input_dialog* id = na->infoDialog;
	
	string name = id->input.at(0)->value();
	string str_number = id->input.at(1)->value();
	int number;

	if (!Utility::valid_int_input(str_number, number))
	{
		fl_message("Invalid number. Please try again.");
		return;
	}
	
	string phone;
	string email;

	if (na->role == BC)
	{
		phone = id->input.at(2)->value();
		email = id->input.at(3)->value();
		na->shop.create_new_customer(name, number, phone, email, na->username, na->password);
		fl_message("New account has been created successfully.");
	}
	else if (na->role == SA)
	{
		na->shop.create_new_sales_associate(name, number, na->username, na->password);
		fl_message("New account has been saved. Please wait for us to validate your information. This may take hours.");
	}
	id->hide();
}

/////--------------------------------------------------------------

///////////////
////	LOGIN WINDOW
///////////////

Login_window::Login_window(Shop& sh, Role& r, int& _position, bool& _exit) : shop(sh), role{r}, position{_position}, exit{_exit}
{
	vector<Fl_Callback*> vCB;
	vCB.push_back(loginCB);
	vCB.push_back(createloginCB);
	vCB.push_back(exitCB);
	
	ld = new Login_dialog(vCB, this);
	Fl::run();
}

void Login_window::loginCB(Fl_Widget* w, void* p)
{
	Login_window* lw = (Login_window*) p;
	Login_dialog* ld = lw->ld;

	string username = ld->username->value();
	string password = ld->password->value();
	
	if (!Utility::find_account(lw->shop, username, password, lw->role, lw->position))
	{
		fl_message_title("Message");
		fl_message("We cannot recognize this account. \nPlease make sure that your username and password are correct.");
		return;
	}
	ld->hide();
	//lw->na->cd->hide();
	//lw->na->infoDialog->hide();
}

void Login_window::createloginCB(Fl_Widget* w, void* p)
{
	Login_window* lw = (Login_window*) p;

	lw->na = new New_account(lw->shop);
	delete lw->na;
}

void Login_window::exitCB(Fl_Widget* w, void* p)
{
	Login_window* lw = (Login_window*) p;
	
	lw->exit = true;
	lw->ld->hide();
}

////--------------------------------------------------------------

///////////////
////	DISPLAY PART DIALOG
///////////////

Display_part_dialog::Display_part_dialog(View& v) : view(v)
{
	vCB.push_back(browserCB);
	browser = new Browser_dialog("View Robot Parts", v.vector_all_part_title(), v.vector_all_part_image(), v.vector_all_part_details(), vCB, this);
	Fl::run();
}

void Display_part_dialog::browserCB(Fl_Widget* w, void* p)
{
	Display_part_dialog* dialog = (Display_part_dialog*) p;
	dialog->browser->hide();
}

///////////////
/////-------------------End DISPLAY PART DIALOG----------------------
///////////////

///////////////
////	DISPLAY MODEL DIALOG
///////////////


Display_model_dialog::Display_model_dialog(View& v) : view(v)
{
	vCB.push_back(browserCB);
	browser = new Browser_dialog("View Models", v.vector_all_model_title(), v.vector_all_model_image(), v.vector_all_model_details(), vCB, this);
	Fl::run();
}

void Display_model_dialog::browserCB(Fl_Widget* w, void* p)
{
	Display_part_dialog* dialog = (Display_part_dialog*) p;
	dialog->browser->hide();
}


///////////////
/////-------------------End DISPLAY PART DIALOG----------------------
///////////////

/////////////////
//////		CHOOSE MODEL DIALOG
/////////////////

Choose_model_dialog::Choose_model_dialog(View& v) : view(v)
{
	vCB.push_back(browserCB);
	browser = new Browser_dialog("Choose Model", v.vector_all_model_title(), v.vector_all_model_image(), v.vector_all_model_details(), vCB, this);
}

void Choose_model_dialog::browserCB(Fl_Widget* w, void* p)
{
	Choose_model_dialog* cd = (Choose_model_dialog*) p;
	
	cd->choice = cd->browser->choice;
	cd->browser->hide();
}

/////---------------------------------------------------------

///////////////
////	CREATE PART DIALOG
///////////////

Create_part_dialog::Create_part_dialog(Shop& sh, View& v) : shop{sh}, view{v}
{
	///// Prompt for part
	int choice;
	
	choice = Utility::get_cmd(view.part_menu(), "Please select a robot part: ", "Create Robot Part");
	
	if (choice == 0)
	{
		return;
	}
	
	part_t p = (part_t) (choice - 1);
	pt = p;

	///// Create entries for dialog
	vector<const char*> entry;
	entry.push_back("Name: ");
	entry.push_back("Model \nnumber: ");
	entry.push_back("Cost: ");
	entry.push_back("Weight: ");
	entry.push_back("Description: ");
	entry.push_back("Image \nfilename: ");

	if (pt == HEAD)
	{
		entry.push_back("Power: ");
	}

	else if (pt == ARM)
	{
		entry.push_back("Max \npower: ");
	}	
	
	else if (pt == LOCOMOTOR)
	{ 
		entry.push_back("Max \nspeed: ");
		entry.push_back("Max \npower: ");
	}
	else if (pt == BATTERY)
	{
		entry.push_back("Max \nenergy: ");
		entry.push_back("Power \navailable: ");
	}
	else if (pt == TORSO)
	{
		entry.push_back("Battery \ncompartments \n(1 to 3): ");
	}
	
	//// Vector 
	vCB.push_back(dialogCB);
	
	dialog = new Input_dialog("Create Robot Part", entry, vCB, this);
	Fl::run();
}

void Create_part_dialog::dialogCB(Fl_Widget* w, void* p)
{
	Create_part_dialog* dm = (Create_part_dialog*) p;
	Input_dialog* id = dm->dialog;
	part_t pt = dm->pt;

	// Get input from dialog

	vector<double> output;
	vector<string> org_output;
	for (int i = 0 ; i < id->input.size() ; i++)
	{
		org_output.push_back(id->input.at(i)->value());
	}

	// Validate inputs
	if (!Utility::valid_input_part(org_output, pt, output))
	{
		fl_message("Invalid input. Please try again!");
		return;
	}
	
	// Add new part
	dm->shop.create_new_robot_part(pt, org_output.at(0), (int) output.at(0), output.at(1), output.at(2), org_output.at(4), org_output.at(5), output.at(3), output.at(4));
	string msg = "Robot part has been created successfull\n\n"/* + view.display_string_part(shop.get_part_size()-1)*/;
	fl_message_title("Create Robot Part");
	fl_message(msg.c_str());
	id->hide();
}

///////////////
////----------------------End CREATE PART DIALOG----------------------
///////////////

///////////////
////	CREATE MODEL DIALOG
///////////////

Create_model_dialog::Create_model_dialog(Shop& sh, View& view) : shop{sh}, v{view}
{
	vCB.push_back(infoDialogCB);
	vCB.push_back(headDialogCB);
	vCB.push_back(torsoDialogCB);
	vCB.push_back(locomotorDialogCB);
	vCB.push_back(armDialogCB);
	vCB.push_back(armDialogCB);
	vCB.push_back(batteryDialogCB);
	//vCB.push_back(createCB);	
	
	vector<const char*> entry;
	entry.push_back("Name: ");
	entry.push_back("Model \nnumber: ");
	entry.push_back("Image \nfilename: ");
	
	infoDialog = new Input_dialog("Create Robot Model", entry, vCB, this);
	Fl::run();
}

void Create_model_dialog::infoDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Input_dialog* id = cd->infoDialog;

	string name;
	int model_number;
	string image_filename;
	
	name = id->input.at(0)->value();
	if (!Utility::valid_int_input(id->input.at(1)->value(), model_number))
	{
		fl_message_title("Invalid input");
		fl_message("Model number must contain only numbers. Please try again.");
		return;
	}
	image_filename = id->input.at(2)->value();

	cd->name = name;
	cd->model_number = model_number;
	cd->image_filename = image_filename;
	id->hide();
	cd->browser = new Browser_dialog("Choose HEAD", cd->v.vector_all_part_title(HEAD), cd->v.vector_all_part_image(HEAD), cd->v.vector_all_part_details(HEAD), cd->vCB, cd);
}

void Create_model_dialog::headDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Browser_dialog* b = cd->browser;

	int choice = b->choice;	
	if (choice == 0)
	{
		fl_message_title("Message");
		fl_message("Please pick one part to continue.");
		return;
	}
	choice--;	

	Robot_part* ropa = cd->shop.get_part(HEAD, choice);
	cd->rp.push_back(ropa);
	b->hide();

	cd->cost += ropa->get_cost();
	cd->power_consumption += ropa->get_power();

	cd->browser = new Browser_dialog("Choose TORSO", cd->v.vector_all_part_title(TORSO), cd->v.vector_all_part_image(TORSO), cd->v.vector_all_part_details(TORSO), cd->vCB, cd);
}

void Create_model_dialog::torsoDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Browser_dialog* b = cd->browser;
	
	int choice = b->choice;	
	if (choice == 0)
	{
		fl_message_title("Message");
		fl_message("Please pick one part to continue.");
		return;
	}
	choice--;

	Robot_part* ropa = cd->shop.get_part(TORSO, choice);
	cd->rp.push_back(ropa);
	b->hide();

	cd->batterycount = ropa->get_battery_compartments();
	cd->cost += ropa->get_cost();	

	cd->browser = new Browser_dialog("Choose LOCOMOTOR", cd->v.vector_all_part_title(LOCOMOTOR), cd->v.vector_all_part_image(LOCOMOTOR), cd->v.vector_all_part_details(LOCOMOTOR), cd->vCB, cd);
}

void Create_model_dialog::locomotorDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Browser_dialog* b = cd->browser;

	int choice = b->choice;	
	if (choice == 0)
	{
		fl_message_title("Message");
		fl_message("Please pick one part to continue.");
		return;
	}
	choice--;	

	Robot_part* ropa = cd->shop.get_part(LOCOMOTOR, choice);
	cd->rp.push_back(ropa);
	b->hide();

	cd->cost += ropa->get_cost();
	cd->power_consumption += ropa->get_power();

	cd->handcount--;
	cd->browser = new Browser_dialog("Choose ARM 1", cd->v.vector_all_part_title(ARM), cd->v.vector_all_part_image(ARM), cd->v.vector_all_part_details(ARM), cd->vCB, cd);
}

// ARM

void Create_model_dialog::armDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Browser_dialog* b = cd->browser;

	int choice = b->choice;	
	if (choice == 0)
	{
		fl_message_title("Message");
		fl_message("Please pick one part to continue.");
		return;
	}
	choice--;	

	Robot_part* ropa = cd->shop.get_part(ARM, choice);
	cd->rp.push_back(ropa);
	b->hide();

	cd->cost += ropa->get_cost();
	cd->power_consumption += ropa->get_power();

	if (cd->handcount > 0)
	{
		cd->browser = new Browser_dialog("Choose ARM 2", cd->v.vector_all_part_title(ARM), cd->v.vector_all_part_image(ARM), cd->v.vector_all_part_details(ARM), cd->vCB, cd);
		cd->handcount--;
	}
	else
	{
		//cout << cd->batterycount << endl;
		cd->batterycount--;
		cd->browser = new Browser_dialog("Choose BATTERY 1", cd->v.vector_all_part_title(BATTERY), cd->v.vector_all_part_image(BATTERY), cd->v.vector_all_part_details(BATTERY), cd->vCB, cd);
	}
}

// BATTERY

void Create_model_dialog::batteryDialogCB(Fl_Widget* w, void* p)
{
	Create_model_dialog* cd = (Create_model_dialog*) p;
	Browser_dialog* b = cd->browser;

	int choice = b->choice;	
	if (choice == 0)
	{
		fl_message_title("Message");
		fl_message("Please pick one part to continue.");
		return;
	}
	choice--;	

	Robot_part* ropa = cd->shop.get_part(BATTERY, choice);
	cd->rp.push_back(ropa);
	b->hide();

	cd->cost += ropa->get_cost();
	cd->power_available += ropa->get_power();

	if (cd->batterycount > 0)
	{
		cd->vCB.push_back(batteryDialogCB);
		string title = "Choose BATTERY ";
		title += to_string(4-cd->batterycount);
		cd->batterycount--;
		cd->browser = new Browser_dialog(title.c_str(), cd->v.vector_all_part_title(BATTERY), cd->v.vector_all_part_image(BATTERY), cd->v.vector_all_part_details(BATTERY), cd->vCB, cd);
	}
	else
	{
		if (cd->power_available < cd->power_consumption)
		{
			cd->cost = 0;
			cd->power_consumption = 0; cd->power_available = 0;
			cd->rp.clear();
			cd->handcount = 2;
			cd->batterycount = 0;			

			fl_message_title("Message");
			fl_alert("Limited power (from batteries) to support other parts. Please choose again!");
			
			cd->vCB.clear();
			cd->vCB.push_back(headDialogCB);
			cd->vCB.push_back(torsoDialogCB);
			cd->vCB.push_back(locomotorDialogCB);
			cd->vCB.push_back(armDialogCB);
			cd->vCB.push_back(armDialogCB);
			cd->vCB.push_back(batteryDialogCB);
			
			cd->browser = new Browser_dialog("Choose HEAD", cd->v.vector_all_part_title(HEAD), cd->v.vector_all_part_image(HEAD), cd->v.vector_all_part_details(HEAD), cd->vCB, cd);
		}
		else
		{
			string msg= "Total cost of this model is $" + to_string(cd->cost) + "\n\nPrice: ";
			double price = Utility::get_double_input(msg);
			
			if (price == -1)
				return;
			
			cd->shop.create_new_robot_model(cd->name, cd->model_number, cd->image_filename, price, cd->rp);
			
			fl_message("Robot model has been created successfully.\n");
		}
	}
}

///////////////
////----------------------End CREATE MODEL DIALOG----------------------
///////////////

///////////////
////		CREATE SALES ASSOCIATE
///////////////

Create_sa_dialog::Create_sa_dialog(Shop& sh, Role r) : shop(sh), role(r)
{
	vector<const char*> item;
	item.push_back("Name: ");
	item.push_back("Employee \nnumber: ");

	vCB.push_back(infoCB);
	vCB.push_back(passCB);	

	infoDialog = new Input_dialog("Create sales associate", item, vCB, this);
	Fl::run();
}

void Create_sa_dialog::infoCB(Fl_Widget* w, void* p)
{
	Create_sa_dialog* cd = (Create_sa_dialog*) p;
	Input_dialog* dialog = cd->infoDialog;

	int employee_number;
	if (!Utility::valid_int_input(dialog->input.at(1)->value(), employee_number))
	{
		fl_message("Invalid model number.");
		return;
	}
	
	cd->name = dialog->input.at(0)->value();
	cd->employee_number = employee_number;

	dialog->hide();
	cd->passDialog = new Create_account_dialog("New sales associate", cd->vCB, cd);
}

void Create_sa_dialog::passCB(Fl_Widget* w, void* p)
{
	Create_sa_dialog* cd = (Create_sa_dialog*) p;
	Create_account_dialog* dialog = cd->passDialog;
	
	string password = dialog->password->value();
	string confirm = dialog->confirm->value();
	if (password != confirm)
	{
		fl_message("Please confirm your password again.");
		return;
	}
	if (!Utility::valid_account(cd->shop, dialog->username->value()))
	{
		fl_message("Username already taken. Please pick another.");
		return;
	}
	
	cd->username = dialog->username->value();
	cd->password = password;

	cd->shop.create_new_sales_associate(cd->name, cd->employee_number, cd->username, cd->password);
	
	if (cd->role == PB)
		cd->shop.get_sales_associate(cd->shop.get_sales_associate_size() - 1)->set_active(true);

	dialog->hide();
	fl_message("Sales associate has been created.");
}

/////-----------------------------------------------------------------

///////////////
////		CREATE BELOVED CUSTOMER
///////////////

Create_bc_dialog::Create_bc_dialog(Shop& sh, Role r) : shop(sh), role(r)
{
	vector<const char*> item;
	item.push_back("Name: ");
	item.push_back("Customer \nnumber: ");
	item.push_back("Phone \nnumber: ");
	item.push_back("Email \naddress: ");

	vCB.push_back(infoCB);
	vCB.push_back(passCB);	

	infoDialog = new Input_dialog("Create beloved customer", item, vCB, this);
	Fl::run();
}

void Create_bc_dialog::infoCB(Fl_Widget* w, void* p)
{
	Create_bc_dialog* cd = (Create_bc_dialog*) p;
	Input_dialog* dialog = cd->infoDialog;

	int number;
	if (!Utility::valid_int_input(dialog->input.at(1)->value(), number))
	{
		fl_message("Invalid model number.");
		return;
	}
	
	cd->name = dialog->input.at(0)->value();
	cd->number = number;
	cd->phone = dialog->input.at(2)->value();
	cd->email = dialog->input.at(3)->value();

	dialog->hide();
	cd->passDialog = new Create_account_dialog("New beloved customer", cd->vCB, cd);
}

void Create_bc_dialog::passCB(Fl_Widget* w, void* p)
{
	Create_bc_dialog* cd = (Create_bc_dialog*) p;
	Create_account_dialog* dialog = cd->passDialog;
	
	string password = dialog->password->value();
	string confirm = dialog->confirm->value();
	if (password != confirm)
	{
		fl_message("Please confirm your password again.");
		return;
	}
	if (!Utility::valid_account(cd->shop, dialog->username->value()))
	{
		fl_message("Username already taken. Please pick another.");
		return;
	}
	
	cd->username = dialog->username->value();
	cd->password = password;

	cd->shop.create_new_customer(cd->name, cd->number, cd->phone, cd->email, cd->username, cd->password);
	
	if (cd->role == PB)
		cd->shop.get_sales_associate(cd->shop.get_customer_size() - 1)->set_active(true);

	dialog->hide();
	fl_message("Beloved customer has been created.");
}

/////-----------------------------------------------------------------

Create_order_dialog::Create_order_dialog(Shop& sh, View& v, int _sa) : shop(sh), view(v), sa(_sa)
{
	vCB.push_back(bdCB);
	vCB.push_back(idCB);
	vCB.push_back(mdCB);

	vector<string> img_filename;
	bd = new Browser_dialog("Choose Beloved Customer", view.vector_all_customer_title(), img_filename, view.vector_all_customer_details(), vCB, this);
	Fl::run();
}

void Create_order_dialog::bdCB(Fl_Widget* w, void* p)
{
	Create_order_dialog* cd = (Create_order_dialog*) p;
	Browser_dialog* bd = cd->bd;

	cd->bc = bd->choice - 1;
	if (cd->bc < 0)
	{
		fl_message("Please pick one.");
		return;
	}	
	
	vector<const char*> entry;
	entry.push_back("Order \nnumber: ");

	bd->hide();
	cd->id = new Input_dialog("New order", entry, cd->vCB, cd);
	
}

void Create_order_dialog::idCB(Fl_Widget* w, void* p)
{
	Create_order_dialog* cd = (Create_order_dialog*) p;
	Input_dialog* id = cd->id;
	
	if (!Utility::valid_int_input(id->input.at(0)->value(), cd->order_number))
	{
		fl_message_title("Message");
		fl_message("Please enter a number.");
		return;
	}

	id->hide();
	
	cd->md = new Browser_dialog("Choose model", cd->view.vector_all_model_title(), cd->view.vector_all_model_image(), cd->view.vector_all_model_details(), cd->vCB, cd);
}

void Create_order_dialog::mdCB(Fl_Widget* w, void* p)
{
	Create_order_dialog* cd = (Create_order_dialog*) p;
	Browser_dialog* md = cd->md;
	
	cd->robot_model = md->choice - 1;
	md->hide();

	if (cd->robot_model < 0)
	{
		fl_message("Please pick one.");
		return;
	}
	
	//// Price
	Robot_model* rm = cd->shop.get_model(cd->robot_model);

	cd->price.subtotal = rm->get_price();
	
	stringstream ss; 
	ss << "Subtotal: $" << cd->price.subtotal << endl;
	cd->price.tax = cd->price.tax*cd->price.subtotal;	
	ss << "Tax: $" << cd->price.tax << endl;
	cd->price.shipping = 15 * rm->weight() / 100;
	ss << "Tax: $" << cd->price.shipping << endl;
	
	string msg = ss.str();
	fl_message(msg.c_str());

	cd->shop.create_new_order(cd->order_number, rm, cd->price, cd->shop.get_sales_associate(cd->sa), cd->shop.get_customer(cd->bc));

	fl_message("Order has been placed and is being processed.");
}


