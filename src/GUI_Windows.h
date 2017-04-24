#ifndef GUI_WIN_H
#define GUI_WIN_H

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

vector<string> run_input_win(int w, int h, const char* title, vector<const char*> entry);

class Input_win : public Fl_Window
{
public:
	Input_win(int w, int h, const char* title, vector<const char*> entry, Shop& sh, Object o, void* p1 = NULL);
	vector<Fl_Input*> input;
	Fl_Button* create;
	Fl_Button* cancel;
	vector<string> get_output();
	void add_output(const char* in);
	void clear_output();
	void* get_ptr();

	void* p1;
	

private:
	vector<string> output;
	Object o;
	Shop& shop;
	bool changed = false;

	static void cb_cancel(Fl_Widget* w, void* p);
	inline void cb_cancel_i();

	static void cb_create_part(Fl_Widget* w, void* p);
	inline void cb_create_i();
};

#endif
