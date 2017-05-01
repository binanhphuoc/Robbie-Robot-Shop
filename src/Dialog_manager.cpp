#include "Dialog_manager.h"
#include "Browser_dialog.h"
#include "Input_dialog.h"
#include <FL/Fl.H>
#include <iostream>

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

Create_sa_dialog::Create_sa_dialog(Shop& sh, Roll r) : shop(sh), roll(r)
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
	
	cd->username = dialog->username->value();
	cd->password = password;

	cd->shop.create_new_sales_associate(cd->name, cd->employee_number, cd->username, cd->password);
	
	if (cd->roll == PB)
		cd->shop.get_sales_associate(cd->shop.get_sales_associate_size() - 1)->set_active(true);

	dialog->hide();
	fl_message("Sales associate has been created.");
}

/////-----------------------------------------------------------------
