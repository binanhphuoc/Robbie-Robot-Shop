#include "Login_dialog.h"
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>

Login_dialog::Login_dialog(vector<Fl_Callback*>& _fxCB, void* _Dialog_manager) : Fl_Window(400, 100+50*5, "Welcome to Robbie Robot Shop"), fxCB{_fxCB}, Dialog_manager{_Dialog_manager}
{
	begin();
	
	callback(fxCB.at(2), Dialog_manager);	

	Fl_Box* box2 = new Fl_Box(0, 0, 400, 50*5);
	Fl_PNG_Image* img = new Fl_PNG_Image("Robot_Images/head_antennaeless.png");
	box2->image(img);

	box = new Fl_Box(0, 0, 400, 100);
	box->label(_FL_ENGRAVED_LABEL, "ROBBIE ROBOT SHOP");
	box->labelcolor(FL_DARK_BLUE);
	box->labelsize(30);
	
	int y = 100;

	username = new Fl_Input(120, y, 180, 30, "Username: ");
	y += 50;

	password = new Fl_Secret_Input(120, y, 180, 30, "Password: ");
	y += 50;	

	login = new Fl_Return_Button(120, y, 150, 30, "Login");
	y+= 50;
	login->callback(fxCB.at(0), Dialog_manager);

	create_account = new Fl_Button(120, y, 150, 30, "Create new account");
	y += 50;
	create_account->callback(fxCB.at(1), Dialog_manager);

	quit = new Fl_Button(120, y, 150, 30, "Quit");
	quit->callback(fxCB.at(2), Dialog_manager);

	end();
	show();
}

void Login_dialog::quitCB(Fl_Widget* w, void* p)
{
	Login_dialog* ld = (Login_dialog*) p;
	ld->hide();
}
