# Makefile for Library
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -L/usr/local/lib -lfltk -lXext -lX11 -lm -lfltk_images

all: exe

debug: CXXFLAGS += -g
debug: exe

rebuild: clean exe

exe: controller.o view.o shop.o order.o robotmodel.o guiwin.o guimainwin.o utility.o main.o
	$(CXX) $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o exe controller.o view.o shop.o order.o robotmodel.o guiwin.o guimainwin.o utility.o main.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o main.o main.cpp

guimainwin.o: GUI_MainWin.cpp GUI_MainWin.h controller.o utility.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o guimainwin.o GUI_MainWin.cpp

utility.o: Utility.cpp Utility.h Robot_part.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o utility.o Utility.cpp

controller.o: Controller.cpp Controller.h view.o guiwin.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o controller.o Controller.cpp

guiwin.o: GUI_Dialog.cpp GUI_Dialog.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o guiwin.o GUI_Dialog.cpp

view.o: View.cpp View.h shop.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o view.o View.cpp

shop.o: Shop.cpp Shop.h order.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o shop.o Shop.cpp

order.o: Order.cpp Order.h Customer.h Sales_associate.h robotmodel.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o order.o Order.cpp

robotmodel.o: Robot_model.cpp Robot_model.h Robot_part.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o robotmodel.o Robot_model.cpp

clean:
	-rm -f *.o exe
