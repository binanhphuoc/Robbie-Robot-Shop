#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <FL/Fl_Box.H>

using namespace std;

Fl_Hold_Browser* browser;
Fl_Window* win;
Fl_Box* box;

void CBbrowser(Fl_Widget* w, void* p)
{
	Fl_Hold_Browser* pp = (Fl_Hold_Browser*) p;
	switch (pp->value())
	{
		case 1:
		{
			cout << 1 << endl;
			break;
		}
		case 2:
		{
			cout << 2<< endl;
			break;
		}
		case 3:
		{
			cout << 3<< endl;
			break;
		}
	}
}

int main()
{
	win = new Fl_Window(550, 550, "Test Win");
	win->callback([](Fl_Widget* w, void* p){w->hide();});
	win->begin();
	browser = new Fl_Hold_Browser(10,10,500,500);
	browser->add("One");               
	browser->add("Two");
	browser->add("Three");
	browser->callback(CBbrowser, browser);
	win->end();
	browser->show();
	win->show();
	return(Fl::run());
}
