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
