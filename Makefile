# Makefile for Library
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -L/usr/local/lib -lfltk -lXext -lX11 -lm

all: exe

debug: CXXFLAGS += -g
debug: exe

rebuild: clean exe

exe: controller.o view.o shop.o order.o robotmodel.o
	$(CXX) $(CXXFLAGS) $(fltk-config --cxxflags) -o exe controller.o view.o shop.o order.o robotmodel.o $(LDFLAGS)

controller.o: Controller.cpp Controller.h view.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o controller.o Controller.cpp

view.o: View.cpp View.h shop.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o view.o View.cpp

shop.o: Shop.cpp Shop.h order.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o shop.o Shop.cpp

order.o: Order.cpp Order.h Customer.h Sales_associate.h robotmodel.o
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o order.o Order.cpp

robotmodel.o: Robot_model.cpp Robot_model.h Robot_part.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o robotmodel.o Robot_model.cpp

clean:
	-rm -f *.o exe
