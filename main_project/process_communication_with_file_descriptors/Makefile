default: all

parent:
	g++ -std=c++11 ./main_parent.cpp -o app1

child:
	g++ -std=c++11 ./main_child.cpp -o app2

all: parent child

clean:
	rm -rf app1 app2
