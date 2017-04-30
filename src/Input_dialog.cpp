#include "Input_dialog.h"

#include "Utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>

Input_dialog::Input_dialog(const char* title, vector<const char*> entry, vector<Fl_Callback*> _fxCB, void* _Dialog_manager) : Fl_Window(300, 60 * entry.size(), title), fxCB{_fxCB}, Dialog_manager{_Dialog_manager}
{
	begin();
	int y = -30;
	for (int i = 0; i < entry.size(); i++)
	{
		y += 50;
		Fl_Input* in = new Fl_Input(120, y, 140, 30, entry.at(i));
		input.push_back(in);
	}
	
	y += 50;
	
	create = new Fl_Button(70, y, 70, 30, "Create");
	create->callback(fxCB.at(0), Dialog_manager);
	fxCB.erase(fxCB.begin());	


	cancel = new Fl_Button(160, y, 70, 30, "Cancel");
	cancel->callback(cb_cancel, this);

	end();
	resizable(this);
	show();
}

void Input_dialog::cb_cancel(Fl_Widget* w, void* p)
{
	((Input_dialog*) p)->hide();
}
