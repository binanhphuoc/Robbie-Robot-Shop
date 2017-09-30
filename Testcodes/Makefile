# Makefile for Library
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -L/usr/local/lib -lfltk -lXext -lX11 -lm

all: testProgram

debug: CXXFLAGS += -g
debug: testProgram

rebuild: clean testProgram

testProgram: GUI_Windows.o test.cpp
	$(CXX) $(CXXFLAGS) $(fltk-config --cxxflags) -o testProgram test.cpp GUI_Windows.o $(LDFLAGS)

GUI_Windows.o: GUI_Windows.cpp GUI_Windows.h
	$(CXX) -c $(CXXFLAGS) $(fltk-config --cxxflags) -o GUI_Windows.o GUI_Windows.cpp

clean:
	-rm -f *.o testProgram
