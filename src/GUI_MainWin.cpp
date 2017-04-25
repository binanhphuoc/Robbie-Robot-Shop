#include "GUI_MainWin.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include "Controller.h"

void run_main_win(int w, int h, const char* title, Controller& _c)
{
	GUI_MainWin* main_win = new GUI_MainWin(w, h, title, _c);
}

GUI_MainWin::GUI_MainWin(int w, int h, const char* title, Controller& _c) : Fl_Window(w, h,title), c{_c}
{
	begin();
	color(FL_WHITE);
	
	callback(main0, this);

	whitebox = new Fl_Box(0,0,400,300);
	
	// Install menu bar

	Fl_Menu_Item menuitems[] = { 
		{"&File", 0, 0, 0, FL_SUBMENU},
			{ "&Exit", FL_ALT + FL_F + 4, main0, this},
			{0},
		{"&Create", 0, 0, 0, FL_SUBMENU},
			{ "Robot &Component", 0, main1, this},
			{ "Robot &Model", 0, main4, this},
			{0},
		{"&View", 0, 0, 0, FL_SUBMENU},
			{ "Robot &Part", FL_ALT + 'p', main2, this},
			{ "Robot &Model", FL_ALT + 'm', main5, this},
			{0},
		{0}
	};
	
	menubar = new Fl_Menu_Bar(0, 0, 400, 30);
	menubar->menu(menuitems);
	
	end();
	show();
	Fl::run();
}

void GUI_MainWin::main0(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main0();
	((GUI_MainWin*)p)->hide();
}

void GUI_MainWin::main1(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main1();
}

void GUI_MainWin::main4(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main4();
}

void GUI_MainWin::main2(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main2();
}

void GUI_MainWin::main5(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main5();
}
