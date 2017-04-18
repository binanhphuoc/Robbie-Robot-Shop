#ifndef WIDGET_H
#define WIDGET_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

using namespace std;

class Box : public Fl_Box
{
	string content;
public:
	Box(int X, int Y, int W, int H, const char *l=0	
};

#endif
