# Makefile for Library
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -L/usr/local/lib -lfltk -lXext -lX11 -lm -lfltk_images

all: exe

debug: CXXFLAGS += -g
debug: exe

rebuild: clean exe

exe: controller.o view.o shop.o order.o robotmodel.o guimainwin.o utility.o main.o dialogmanager.o browserdialog.o inputdialog.o createaccountdialog.o logindialog.o state.o
	$(CXX) $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o exe controller.o view.o shop.o order.o robotmodel.o guimainwin.o utility.o main.o inputdialog.o dialogmanager.o browserdialog.o createaccountdialog.o logindialog.o state.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o main.o main.cpp

guimainwin.o: GUI_MainWin.cpp GUI_MainWin.h controller.o utility.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o guimainwin.o GUI_MainWin.cpp

controller.o: Controller.cpp Controller.h view.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o controller.o Controller.cpp

dialogmanager.o: Dialog_manager.cpp Dialog_manager.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o dialogmanager.o Dialog_manager.cpp

logindialog.o: Login_dialog.cpp Login_dialog.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o logindialog.o Login_dialog.cpp

createaccountdialog.o: Create_account_dialog.cpp Create_account_dialog.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o createaccountdialog.o Create_account_dialog.cpp

inputdialog.o: Input_dialog.cpp Input_dialog.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o inputdialog.o Input_dialog.cpp

browserdialog.o: Browser_dialog.cpp Browser_dialog.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o browserdialog.o Browser_dialog.cpp

utility.o: Utility.cpp Utility.h Robot_part.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o utility.o Utility.cpp

view.o: View.cpp View.h shop.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o view.o View.cpp

shop.o: Shop.cpp Shop.h order.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o shop.o Shop.cpp

order.o: Order.cpp Order.h Customer.h Sales_associate.h robotmodel.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o order.o Order.cpp

state.o: State.cpp State.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o state.o State.cpp

robotmodel.o: Robot_model.cpp Robot_model.h Robot_part.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --use-images --cxxflags) -o robotmodel.o Robot_model.cpp

clean:
	-rm -f *.o exe
