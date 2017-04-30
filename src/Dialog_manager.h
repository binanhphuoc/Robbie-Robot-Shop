#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "Browser_dialog.h"
#include "View.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Box.H>

class Display_part_dialog
{
public:
	Display_part_dialog(View& v);
	Browser_dialog* browser;
	View& view;

	static void browserCB(Fl_Widget* w, void* p);
};

#endif
