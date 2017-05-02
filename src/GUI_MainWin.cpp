#include "GUI_MainWin.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include "Controller.h"

GUI_MainWin::GUI_MainWin(int w, int h, const char* title, Controller& _c) : Fl_Window(w, h,title), c{_c}
{
	begin();
	color(FL_WHITE);
	
	callback(main0, this);

	whitebox = new Fl_Box(0,30,400,300);
	Fl_JPEG_Image* background = new Fl_JPEG_Image("Robot_Images/full_button_can.jpg");
	whitebox->image(background);

	// Install menu bar

	menubar = new Fl_Menu_Bar(0, 0, 400, 30);
	

	if (c.role == PB)
	{
		Fl_Menu_Item menuitems[] = { 
			{"&File", 0, 0, 0, FL_SUBMENU},
				{ "&Exit", FL_ALT + FL_F + 4, main0, this},
				{0},
			{"&Create", 0, 0, 0, FL_SUBMENU},
				{ "Robot &Component", 0, main1, this},
				{ "Robot &Model", 0, main4, this},
				{ "&Sales Associate", 0, main9, this},
				{ "&Beloved Customer", 0, main7, this},
				{0},
			{"&View", 0, 0, 0, FL_SUBMENU},
				{ "Robot &Part", FL_ALT + 'p', main2, this},
				{ "Robot &Model", FL_ALT + 'm', main5, this},
				{0},
			{0}
		};
	
		menubar->menu(menuitems);
		resizable(*whitebox);
		end();
		show();
		Fl::run();
	}
	else if (c.role == PM)
	{
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
	
		menubar->menu(menuitems);
		resizable(*whitebox);
		end();
		show();
		Fl::run();
	}
	else if (c.role == BC)
	{
		Fl_Menu_Item menuitems[] = { 
			{"&File", 0, 0, 0, FL_SUBMENU},
				{ "&Exit", FL_ALT + FL_F + 4, main0, this},
				{0},
			{"&View", 0, 0, 0, FL_SUBMENU},
				{ "Robot &Part", FL_ALT + 'p', main2, this},
				{ "Robot &Model", FL_ALT + 'm', main5, this},
				{0},
			{0}
		};
	
		menubar->menu(menuitems);
		resizable(*whitebox);
		end();
		show();
		Fl::run();
	}
	else if (c.role == SA)
	{
		Fl_Menu_Item menuitems[] = { 
			{"&File", 0, 0, 0, FL_SUBMENU},
				{ "&Exit", FL_ALT + FL_F + 4, main0, this},
				{0},
			{"&Create", 0, 0, 0, FL_SUBMENU},
				{ "New &order", 0, main11, this},
				{0},
			{"&View", 0, 0, 0, FL_SUBMENU},
				{ "Robot &Part", FL_ALT + 'p', main2, this},
				{ "Robot &Model", FL_ALT + 'm', main5, this},
				{0},
			{0}
		};
	
		menubar->menu(menuitems);
		resizable(*whitebox);
		end();
		show();
		Fl::run();
	}
	
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

void GUI_MainWin::main7(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main7();
}

void GUI_MainWin::main9(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main9();
}

void GUI_MainWin::main11(Fl_Widget* w, void* p)
{
	((GUI_MainWin*)p)->c.main11();
}
