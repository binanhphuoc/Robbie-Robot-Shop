#ifndef GUI_MAINWIN_H
#define GUI_MAINWIN_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>
#include "Controller.h"

class GUI_MainWin : public Fl_Window
{
public:
	GUI_MainWin(int w, int h, const char* title, Controller& _c);
	Controller& c; 
	Fl_Box* whitebox;
	Fl_Menu_Bar* menubar;

private:
	static void main0(Fl_Widget* w, void* p);
	static void main1(Fl_Widget* w, void* p);
	bool check_available();
	static void main2(Fl_Widget* w, void* p);
	static void main3(Fl_Widget* w, void* p);
	static void main4(Fl_Widget* w, void* p);
	static void main5(Fl_Widget* w, void* p);
	static void main6(Fl_Widget* w, void* p);
	static void main7(Fl_Widget* w, void* p);
	static void main8(Fl_Widget* w, void* p);
	static void main9(Fl_Widget* w, void* p);
	static void main10(Fl_Widget* w, void* p);
	static void main11(Fl_Widget* w, void* p);
	static void main12(Fl_Widget* w, void* p);
};

#endif
