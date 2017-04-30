#ifndef INPUT_DIALOG_H
#define INPUT_DIALOG_H

#include "Robot_part.h"
#include "Utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>

using namespace std;

class Input_dialog : public Fl_Window
{
public:
	Input_dialog(const char* title, vector<const char*> entry, vector<Fl_Callback*> _fxCB, void* _Dialog_manager);
	vector<Fl_Input*> input;
	Fl_Button* create;
	Fl_Button* cancel;
	void* Dialog_manager;
	vector<Fl_Callback*> fxCB;

private:
	static void cb_cancel(Fl_Widget* w, void* p);

};

#endif
