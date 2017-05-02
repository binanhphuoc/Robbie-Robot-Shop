#include "Utility.h"
#include "View.h"
#include "Robot_part.h"
#include <FL/fl_ask.H>
#include <cstring>
#include <string>

using namespace std;

//////////////////////////////////
////////		UTILITY
//////////////////////////////////

int Utility::get_cmd(Menu menu, string prompt, string title)
{
	const char* choice;
	int ch;
	//cout << menu.content;
	string msg = menu.content + "\n" + prompt;
	fl_message_title(title.c_str());
	choice = fl_input(msg.c_str(),"");
	//view.ask("Choice: ");
	//getline(cin, choice);
	if (choice == NULL)
		return 0;
	string choice_str = choice;
	while (!valid_cmd(choice_str, menu.min, menu.max, ch))
	{	
		fl_alert("Invalid input. Please try again!\n\n");
		fl_message_title(title.c_str());
		choice = fl_input(menu.content.c_str(),"");
		if (choice == NULL)
			return 0;
		choice_str = choice;
	}
	
	return ch;
}

bool Utility::valid_cmd(string choice, int min, int max, int& ch)
{
	if (!valid_int_input(choice, ch))
	{
		return false;
	}	
	if (ch < min || ch > max)
	{
		return false;
	}
	else
		return true;
}

bool Utility::isDigit(char c)
{
	if (c == '0' || c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
		return true;
	return false;
}

bool Utility::valid_int_input(string input, int& ch)
{
	const char* str = input.c_str();
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isDigit(str[i]))
		{
			ch = 0;
			return false;
		}
	}
	
	ch = atoi(str);
	//cout << "char = " << ch << endl;
	return true;
}
	
bool Utility::valid_double_input(string input, double& ch)
{
	const char* str = input.c_str();
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isDigit(str[i]) && str[i] != '.')
		{
			ch = 0;
			return false;
		}
	}
	
	ch = atof(str);
	//cout << "char = " << ch << endl;
	return true;
}

bool Utility::valid_input_part(vector<string> input, part_t p, vector<double>& output)
{
	output.clear();
	bool valid = true;
	int model_number;
	double cost, weight, var1, var2;
	if (!valid_int_input(input.at(1), model_number) 
		|| !valid_double_input(input.at(2), cost)
		|| !valid_double_input(input.at(3), weight))
	{
		valid = false;
		return valid;
	}
	output.push_back(model_number);
	output.push_back(cost);
	output.push_back(weight);	

	if (p == HEAD || p == ARM)
	{
		if (!valid_double_input(input.at(6), var1))
		{
			output.clear();		
			valid = false;
			return valid;
		}
		else
		{
			output.push_back(var1);	
			output.push_back(0);
		}
	}
	else if (p == LOCOMOTOR || p == BATTERY)
	{ 
		if (!valid_double_input(input.at(6), var1) || !valid_double_input(input.at(7), var2))
		{
			output.clear();	
			valid = false;
			return valid;		
		}
		else
		{
			output.push_back(var1);
			output.push_back(var2);
		}
	}
	else if (p == TORSO)
	{
		//var1 = (double) get_int_input("Battery compartments (1 to 3): ", 1, 3);
		//var2 = get_double_input("Max arms: ");
		int var = 0;
		if (!valid_cmd(input.at(6), 1, 3, var) )
			/*|| !valid_double_input(input.at(7), var2))*/
		{
			output.clear();	
			valid = false;
			return valid;
		}
		else
		{
			var1 = (double) var;
			output.push_back(var1);
			output.push_back(0);
			//output.push_back(var2);
		}
	}
	return valid;
}

string Utility::get_string_input(string prompt)
{	
	string input = fl_input(prompt.c_str());
	return input;
}

int Utility::get_int_input(string prompt, int min, int max)
{
	//view.ask(prompt);
	string input = fl_input(prompt.c_str());
	int in;
	if (min == -1 || max == -1)
	{
		while (!valid_int_input(input, in))
		{
			fl_alert("Invalid input. Please try again!\n\n");
			input = fl_input(prompt.c_str());
		}
		return in;
	}
	else
	{
		while (!valid_cmd(input, min, max, in))
		{
			string msg = "Input should be a number between " + to_string(min) + " and " + to_string(max) + ". Please try again!\n\n";
			fl_message(msg.c_str());
			input = fl_input(prompt.c_str());
		}
		return in;
	}
}

double Utility::get_double_input(string prompt)
{
	const char* input = fl_input(prompt.c_str());
	if (input == NULL)
			return -1;
	double in;
	while (!valid_double_input(input, in))
	{
		fl_alert("Invalid input. Please try again!\n\n");
		input = fl_input(prompt.c_str());
		if (input == NULL)
			return -1;
	}
	return in;
}

void Utility::scale_image(Fl_Box* box, Fl_JPEG_Image* img)
{
	if (!img) {
	    return; 
	}
	
	
	// Resize the image if it's too big, by replacing it with a resized copy:
	if (img->w() > box->w() || img->h() > box->h()) {
	
	    Fl_Image *temp;
	/*
	    if (img->w() > img->h()) {
		temp = img->copy(box->w(), box->h() * img->h() / img->w());
	    } else {
		temp = img->copy(box->w() * img->w() / img->h(), box->h());
	    }
	*/
	    temp = img->copy(box->w(), box->h());
	    delete img;
	    img = (Fl_JPEG_Image *) temp;
	}
	
	// Assign image to box
	box->image(img);
	box->redraw();
}

void Utility::scale_image(Fl_Box* box, Fl_PNG_Image* img)
{
	if (!img) {
	    return; 
	}

	// Resize the image if it's too big, by replacing it with a resized copy:
	if (img->w() != box->w() || img->h() != box->h()) {
	    Fl_Image *temp;
	/*
	    if (img->w() > img->h()) {
		temp = img->copy(box->w(), box->h() * img->h() / img->w());
	    } else {
		temp = img->copy(box->w() * img->w() / img->h(), box->h());
	    }
	*/
	    temp = img->copy(box->w(), box->h());
	    delete img;
	    img = (Fl_PNG_Image *) temp;
	}
	
	// Assign image to box
	box->image(img);
	box->redraw();
}

int Utility::check_image(string filename)
{
	if(filename.substr(filename.find_last_of(".") + 1) == "png")
	{
		return 1;
	}
	if(filename.substr(filename.find_last_of(".") + 1) == "jpg")
	{
		return 2;
	}
	return 0;
}

bool Utility::valid_account(Shop& shop, string username)
{
	if (username == "pointedhairedboss")
		return false;
	if (username == "productmanager")
		return false;
	for (int i = 0; i < shop.get_sales_associate_size(); i++)
	{
		if (username == shop.get_sales_associate(i)->get_username())
			return false;
	}
	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		if (username == shop.get_customer(i)->get_username())
			return false;
	}
	return true;
}

bool Utility::find_account(Shop& shop, string username, string password, Role& role, int& position)
{
	if (username == "" || password == "")
		return false;
	if (username == "pointedhairedboss" && password == "pointedhairedboss")
	{
		role = PB;
		position = -1;
		return true;
	}
	if (username == "productmanager" && password == "productmanager")
	{
		role = PM;
		position = -1;
		return true;
	}
	
	for (int i = 0; i < shop.get_sales_associate_size(); i++)
	{
		if (username == shop.get_sales_associate(i)->get_username() && password == shop.get_sales_associate(i)->get_password() && shop.get_sales_associate(i)->get_active())
		{
			role = SA;
			position = i;
			return true;
		}
	}

	for (int i = 0; i < shop.get_customer_size(); i++)
	{
		if (username == shop.get_customer(i)->get_username() && password == shop.get_customer(i)->get_password() && shop.get_customer(i)->get_active())
		{
			role = BC;
			position = i;	
			return true;
		}
	}
	
	return false;
}

////////////////////
///-----------------------------------End UTILITY------------------------
////////////////////
