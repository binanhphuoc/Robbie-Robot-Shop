#include "GUI_Windows.h"
#include <vector>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

using namespace std;

int main()
{
	vector<const char*> entry;
	entry.push_back("Name");
	entry.push_back("Age");
	vector<string> output = run_input_win(300, 200, "Hello", entry);
	cout << output.size() << endl;
	return 0;
}
