#include "Create_account_dialog.h"
#include "Utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>

Create_account_dialog::Create_account_dialog(string title, vector<Fl_Callback*>& _fxCB, void* _Dialog_manager) : Fl_Window(300, 50*3 + 60, title.c_str()), fxCB{_fxCB}, Dialog_manager{_Dialog_manager}
{
	begin();

	int y = -30;
	
	y += 50;
	username = new Fl_Input(120, y, 140, 30, "Username: ");
	
	y += 50;
	password = new Fl_Secret_Input(120, y, 140, 30, "Password: ");
	
	y += 50;
	confirm = new Fl_Secret_Input(120, y, 140, 30, "Confirm \npassword: ");
	
	y += 45;
	
	create = new Fl_Button(70, y, 70, 30, "Create");
	create->callback(fxCB.at(0), Dialog_manager);
	fxCB.erase(fxCB.begin());	


	cancel = new Fl_Button(160, y, 70, 30, "Cancel");
	cancel->callback(cb_cancel, this);

	end();
	resizable(this);
	show();
}

void Create_account_dialog::cb_cancel(Fl_Widget* w, void* p)
{
	((Create_account_dialog*) p)->hide();
}
