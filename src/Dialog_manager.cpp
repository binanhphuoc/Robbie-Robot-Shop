#include "Dialog_manager.h"
#include "Browser_dialog.h"
#include <FL/Fl.H>
#include <iostream>

///////////////
////	DISPLAY PART DIALOG
///////////////

Display_part_dialog::Display_part_dialog(View& v) : view(v)
{
	vCB.push_back(browserCB);
	browser = new Browser_dialog("View Robot Parts", v.vector_all_part_title(), v.vector_all_part_image(), v.vector_all_part_details(), vCB, this);
	Fl::run();
}

void Display_part_dialog::browserCB(Fl_Widget* w, void* p)
{
	Display_part_dialog* dialog = (Display_part_dialog*) p;
	dialog->browser->hide();
}
