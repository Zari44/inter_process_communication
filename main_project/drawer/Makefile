CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# LIB_PATH = -L /usr/local/lib/
# LIB = simple2d

# INC_PATH = -I /usr/local/include/

LIBS = application.cpp 
TARGET = drawer

default: main

main:
	$(CXX)  -I . $(CXXFLAGS) $(LIBS) `simple2d --libs` main_drawer.cpp  -o $(TARGET)

# $(TARGET): $(OBJECT_FILES)
# 	 $(CFLAGS) $(INC_PATH) $(LIB_PATH) $(OBJECT_FILES) 

# triangle.o: triangle.c
# 	$(CXX) $(CFLAGS) $(INC_PATH) $(LIB_PATH) -c triangle.c

# clean:
# 	rm -f $(TARGET) $(OBJECT_FILES) 
