CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# drawer
DRAWER_PATH = ./drawer
LIBS = $(DRAWER_PATH)/application.cpp 
DRAWER_TARGET = drawer_app



default: all

drawer:
	$(CXX)  -I $(DRAWER_PATH) $(CXXFLAGS) $(LIBS) `simple2d --libs` $(DRAWER_PATH)/main_drawer.cpp  -o $(DRAWER_TARGET)

ipc: 
	$(CXX) $(CXXFLAGS) ./ipc/main_parent.cpp -o app1
	$(CXX) $(CXXFLAGS) ./ipc/main_child.cpp -o app2

all: ipc drawer

clean:
	rm -f $(DRAWER_TARGET)
	rm -f ./app1 ./app2



# default: all

# parent:
# 	g++ -std=c++11 ./ipc/main_parent.cpp -o app1

# child:
# 	

# all: parent child

# clean:
# 	rm -rf ./app1 ./app2
