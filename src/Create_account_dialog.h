#ifndef CREATE_ACCOUNT_DIALOG_H
#define CREATE_ACCOUNT_DIALOG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <string>
#include <vector>

using namespace std;

class Create_account_dialog : public Fl_Window
{
public:
	Create_account_dialog(string title, vector<Fl_Callback*>& _fxCB, void* _Dialog_manager, bool pickroll = false);
	Fl_Choice* role;
	Fl_Input* username;
	Fl_Secret_Input* password;
	Fl_Secret_Input* confirm;
	Fl_Button* create;
	Fl_Button* cancel;
	void* Dialog_manager;
	vector<Fl_Callback*>& fxCB;

private:
	static void cb_cancel(Fl_Widget* w, void* p);

};

#endif
