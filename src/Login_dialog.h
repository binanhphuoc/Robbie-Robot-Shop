#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <string>
#include <vector>

using namespace std;

class Login_dialog : public Fl_Window
{
public:
	Login_dialog(vector<Fl_Callback*>& _fxCB, void* _Dialog_manager);
	Fl_Box* box;
	Fl_Input* username;
	Fl_Secret_Input* password;
	Fl_Return_Button* login;
	Fl_Button* quit;
	Fl_Button* create_account;
	void* Dialog_manager;
	vector<Fl_Callback*>& fxCB;

private:
	static void quitCB(Fl_Widget* w, void* p);
};

#endif
