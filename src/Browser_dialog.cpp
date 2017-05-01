#include "Browser_dialog.h"
#include "Utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <exception>

/*
Browser_dialog::Browser_dialog(const char* title, vector<string> item, vector<string> _image_filename, vector<string> _details, Fl_Callback* CBfunction, void* _Dialog_Manager) : Fl_Window(500, 480, title), image_filename{_image_filename}, details(_details), functionCB{CBfunction}, Dialog_Manager{_Dialog_Manager}
{
	begin();
	callback(cancelCB, this);
	browser = new Fl_Hold_Browser(10, 10, 240, 420);
	for (int i = 0; i < item.size(); i++)
		browser->add(item.at(i).c_str());
	browser->callback(browserCB, this);
	
	box = new Fl_Box(260, 205, 230, 230);

	buff = new Fl_Text_Buffer();
    	disp = new Fl_Text_Display(260, 10, 230, 185);
	disp->buffer(buff);

	next = new Fl_Button(160, 440, 80, 30, "Next");
	next->callback(functionCB, Dialog_Manager);

	cancel = new Fl_Button(260, 440, 80, 30, "Cancel");
	cancel->callback(cancelCB, this);
	end();
	show();
}
*/

Browser_dialog::Browser_dialog(const char* title, vector<string> item, vector<string> _image_filename, vector<string> _details, vector<Fl_Callback*>& CBfunction, void* _Dialog_Manager) : Fl_Window(500, 480, title), image_filename{_image_filename}, details(_details), vCB{CBfunction}, Dialog_Manager{_Dialog_Manager}
{
	begin();
	callback(cancelCB, this);
	browser = new Fl_Hold_Browser(10, 10, 240, 420);
	for (int i = 0; i < item.size(); i++)
		browser->add(item.at(i).c_str());
	browser->callback(browserCB, this);
	
	box = new Fl_Box(260, 205, 230, 230);

	buff = new Fl_Text_Buffer();
    	disp = new Fl_Text_Display(260, 10, 230, 185);
	disp->buffer(buff);

	next = new Fl_Button(160, 440, 80, 30, "Next");
	next->callback(vCB.at(0), Dialog_Manager);
	vCB.erase(vCB.begin());

	cancel = new Fl_Button(260, 440, 80, 30, "Cancel");
	cancel->callback(cancelCB, this);
	end();
	show();
}

void Browser_dialog::browserCB(Fl_Widget* w, void* p)
{
	Browser_dialog* bd = (Browser_dialog*) p;
	int index = bd->browser->value();
	bd->choice = index;
	if (index == 0)
	{
		bd->buff->text("");
		return;
	}

	bd->buff->text(bd->details.at(index-1).c_str());
	
	//Image loading
	if (bd->box->image() != NULL)
	{
		delete (bd->box->image());
	}

	int check = Utility::check_image(bd->image_filename.at(index-1));
	if (check == 1)
	{
		Fl_PNG_Image* img = new Fl_PNG_Image(bd->image_filename.at(index-1).c_str());
		if (img)
		{
			Utility::scale_image(bd->box, img);
			return;
		}	
	}
	else if (check == 2)
	{
		Fl_JPEG_Image* img = new Fl_JPEG_Image(bd->image_filename.at(index-1).c_str());
		if (img)
			Utility::scale_image(bd->box, img);
		return;
	}
	else
	{
		bd->box->image(NULL);
		bd->box->label("");
		bd->box->redraw();
	}
	//cout << bd->image_filename.at(index-1) << endl;
	
}

void Browser_dialog::cancelCB(Fl_Widget* w, void* p)
{
	((Browser_dialog*) p)->hide();
}
