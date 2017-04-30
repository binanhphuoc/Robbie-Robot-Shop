#ifndef BROWSER_INPUT_DIALOG_H
#define BROWSER_INPUT_DIALOG_H

#include <string>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>

using namespace std;

class Browser_dialog : public Fl_Window
{
public:
	//Browser_dialog(const char* title, vector<string> item, vector<string> _image_filename, vector<string> details, Fl_Callback* _CBfunction, void* _Dialog_Manager);
	Browser_dialog(const char* title, vector<string> item, vector<string> _image_filename, vector<string> details, vector<Fl_Callback*> _CBfunction, void* _Dialog_Manager);
	Fl_Hold_Browser* browser;
	Fl_Box* box;
	Fl_Text_Buffer* buff;
	Fl_Text_Display* disp;
	Fl_Button* next;
	Fl_Button* cancel;

	int choice;
	vector<string> image_filename;
	vector<string> details;
	//Fl_Callback* functionCB;
	vector<Fl_Callback*> vCB;
	void* Dialog_Manager;

private:

	static void browserCB(Fl_Widget* w, void* p);
	//static void nextCB(Fl_Widget* w, void* p);
	static void cancelCB(Fl_Widget* w, void* p);
};

#endif
