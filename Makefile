CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# main app
MAIN_PATH = ./main
MAIN_TARGET = main_app

# drawer
DRAWER_PATH = ./drawer
LIBS = $(DRAWER_PATH)/application.cpp 
DRAWER_TARGET = drawer_app

drawer:
	$(CXX) $(CXXFLAGS) -I $(DRAWER_PATH) $(LIBS) `simple2d --libs` $(DRAWER_PATH)/main_drawer.cpp  -o $(DRAWER_TARGET)

main: 
	$(CXX) $(CXXFLAGS) $(MAIN_PATH)/main_app.cpp -o $(MAIN_TARGET)

all: main drawer

default: all

clean:
	rm -f $(DRAWER_TARGET)
	rm -f $(MAIN_TARGET)

