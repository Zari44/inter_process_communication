application1:
	g++ ./parent/main.cpp -o app1
application2:
	g++ ./child/main.cpp -o app2

all: application1 application2
